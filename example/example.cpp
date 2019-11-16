#include <iostream>
#include <thread>
#include <signal.h>
#include <memory>


#include "OutputSysfs.h"
#include "InputSysfs.h"
#include "InputGpioLib.h"
#include "OutputGpioLib.h"
#include "InputPin.h"
#include "DebouncedInput.h"
#include "SoftTimer.h"
#include <pthread.h>


using namespace std;

static bool stop=false;

/**
 * @brief handleSignals-in case of termination, free resources
 */
void handleSignals(int){
    static bool shutdownInProgress=false;
    cout<<"Termination event"<<endl;
    if(!shutdownInProgress){
        stop=true;
        shutdownInProgress=true;
    }
    else{
        cout<<"app is shutting down"<<endl;
    }
}

/**
 * @brief Callback in case of on event from debounced input
 */
void DebouncedOnEvent(){
    cout<<endl<<"---Async debounced: ON event!---"<<endl;
}
/**
 * @brief Callback in case of off event from debounced input
 */
void DebouncedOffEvent(){
    cout<<endl<<"---Async debounced: OFF event!---"<<endl;
}

/**
 * @brief Callback from raw input wrapper
 */
void eventCb(bool val){
    if(val)
        cout<<"eventcb - ON"<<endl;
    else
        cout<<"eventcb - OFF"<<endl;
}
int main(){
    try{
        //signal hangling (ctrl+c, or service termination)
        struct sigaction sigHandler;
        sigHandler.sa_handler=handleSignals;
        sigemptyset(&sigHandler.sa_mask);
        sigHandler.sa_flags=0;
        sigaction(SIGTERM,&sigHandler,NULL);
        sigaction(SIGINT,&sigHandler,NULL);

        //create input/output based on sysfs implementation
        shared_ptr<OutputPin> out_pin_sysfs=make_shared<OutputSysfs>(20);
        shared_ptr<InputPin> in_pin_sysfs=make_shared<InputSysfs>(26);

        //create input/output based on gpiolib implementation
        shared_ptr<OutputPin> out_pin_gpiolib=make_shared<OutputGpioLib>("gpiochip0",16);
        shared_ptr<InputPin> in_pin_gpiolib=make_shared<InputGpioLib>("gpiochip0",19);

        //set async input behavior
        in_pin_sysfs->SetPullUpDown(InputPin::PullUpDown::PullDown);
        in_pin_sysfs->SetTriggerEdge(InputPin::TriggerEdge::Both);
        in_pin_gpiolib->SetTriggerEdge(InputPin::TriggerEdge::Both);

        //create debouncer for sysfs input
        shared_ptr<BasicTimer> timer=make_shared<SoftTimer>();
        DebouncedInput<>debouncedAsyncInput(*in_pin_sysfs,*timer);

        //set callback for debounced input and raw gpiolib input
        debouncedAsyncInput.setOnCallback(DebouncedOnEvent);
        debouncedAsyncInput.setOffCallback(DebouncedOffEvent);
        in_pin_gpiolib->SetEventCallback(eventCb);

        //start async listener process
        in_pin_gpiolib->StartListening();



        cout<<"Running"<<endl;


        int cnt=0;
        //start main loop and change IO state in every 2 seconds
        while (!stop && cnt++<10) {
            cout<<"Set output to ";
            if(cnt%2){
                cout<<"1"<<endl;
                out_pin_sysfs->Write(true);
                out_pin_gpiolib->Write(true);
            }
            else{
                cout<<"0"<<endl;
                out_pin_sysfs->Write(false);
                out_pin_gpiolib->Write(false);
            }
            cout<<"Waiting..." <<flush;
            this_thread::sleep_for(chrono::seconds(2));
            cout<<"-----------------------------"<<endl;
        }

        //stop async process
        in_pin_gpiolib->StopListening();
    }
    catch(...){
        cout<<"Fatal error."<<endl;
    }
    cout<<"Program terminated"<<endl;
}

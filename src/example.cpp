#include <iostream>
#include <thread>
#include <signal.h>
#include <memory>


#include "OutputPort.h"
#include "InputPort.h"
#include "AsyncInput.h"


using namespace std;

static shared_ptr<OutputPort>out_port;
static shared_ptr<InputPort>in_sync;
static shared_ptr<AsyncInput>in_async;


static bool stop=false;
/**
 * @brief shutDown - stop async input listening
 */
void shutDown(){
    cout<<"Shutdown in progress"<<endl;
    if(in_async)
        in_async->StopListening();
    stop=true;
    cout<<"Shutdown finished"<<endl;
}
/**
 * @brief handleSignals-in case of termination, free resources
 */
void handleSignals(int){
    static bool shutdownInProgress=false;
    cout<<"Termination event";
    if(!shutdownInProgress){
        shutdownInProgress=true;
        shutDown();
    }
    else{
        cout<<"app is shutting down"<<endl;
    }
}

void OnEvent(){
    cout<<"Async ON event!"<<endl;
}
void OffEvent(){
    cout<<"Async OFF event!"<<endl;
}

int main(){
    cout<<"Program started"<<endl;
    try{
        out_port=make_shared<OutputPort>(2);
        in_sync=make_shared<InputPort>(3);
        in_async=make_shared<AsyncInput>(14);
        in_async->SetOnCallback(OnEvent);
        in_async->SetOffCallback(OffEvent);

        //signal hangling (ctrl+c, or service termination)
        struct sigaction sigHandler;
        sigHandler.sa_handler=handleSignals;
        sigemptyset(&sigHandler.sa_mask);
        sigHandler.sa_flags=0;
        sigaction(SIGTERM,&sigHandler,NULL);
        sigaction(SIGINT,&sigHandler,NULL);


        in_async->Init();
        in_async->StartListening();
        cout<<"Running"<<endl;
        int cnt=0;
        while (!stop || cnt++>10) {
            this_thread::sleep_for(chrono::seconds(2));
        }
        shutDown();
    }
    catch(...){
        cout<<"Fatal error."<<endl;
        shutDown();
    }
    cout<<"Program terminated"<<endl;
}

#include <sstream>
#include <linux/gpio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

#include "InputGpioLib.h"

using namespace std;


InputGpioLib::InputGpioLib(const char *chipName, uint32_t pinNo):pinNo{pinNo}{
    stringstream ss;
    ss<<"/dev/"<<chipName;
    chipfd = open(ss.str().c_str(), O_RDWR | O_CLOEXEC);
    if(chipfd>=0){
        SetTriggerEdge(InputPin::TriggerEdge::None);
    }
    else
        cerr<<"Unable to open chip: "<<ss.str()<<endl;
}

InputGpioLib::~InputGpioLib(){
    if(fd>=0)
        close(fd);
    if(chipfd>=0)
        close(chipfd);
}

void InputGpioLib::SetTriggerEdge(InputPin::TriggerEdge edge){

    struct gpioevent_request req{};
    req.eventflags=0;
    req.lineoffset=pinNo;
    strcpy(req.consumer_label, "LIO reader");
    req.handleflags=GPIOHANDLE_REQUEST_OPEN_DRAIN;

    switch(edge){
        case TriggerEdge::None:
            break;
        case TriggerEdge::Rising:
            req.eventflags |= GPIOEVENT_REQUEST_RISING_EDGE;
            break;
        case TriggerEdge::Falling:
            req.eventflags |= GPIOEVENT_REQUEST_FALLING_EDGE;
            break;
        case TriggerEdge::Both:
            req.eventflags |= GPIOEVENT_REQUEST_BOTH_EDGES;
            break;
    }
    if(chipfd>=0){
        if(fd>=0){
            close(fd);
            fd=-1;
        }
        int ret=ioctl(chipfd,GPIO_GET_LINEEVENT_IOCTL,&req);
        if(ret<0)
            cerr<<"Unable to set trigger edge on "<<pinNo<<". Err: "<<strerror(errno)<<endl;
        else
            fd=req.fd;
    }
}


bool InputGpioLib::Read(){
    if(isOk()){
        gpiohandle_data data;
        if(ioctl(fd,GPIOHANDLE_GET_LINE_VALUES_IOCTL,&data)>=0){
            return data.values[0];
        }
        else
            cout<<"unable to perform read operation at "<<pinNo<<endl;
    }
    return false;
}

uint32_t InputGpioLib::GetPinNo(){
    return pinNo;
}

void InputGpioLib::SetPullUpDown(InputPin::PullUpDown pud){
    //Not supported
}

bool InputGpioLib::isOk(){
    return fd>=0 && chipfd >=0;
}



void InputGpioLib::listenerThreadRunnable(std::promise<void> &&threadExitPromise, int fileDescriptor){
    if(fileDescriptor>=0){
        gpioevent_data event;
        int readSize=0;
        while(!threadExitRequest){
            readSize=read(fileDescriptor, &event, sizeof(event));
            if(readSize == -1){
                if(errno == -EAGAIN) //nothing available
                    continue;
                else if(!threadExitRequest){
                    cerr<<"Unable to read event"<<endl;
                    break;
                }
            }
            else if(readSize != sizeof(event) && !threadExitRequest){
                cerr<<"Ivalid event reading"<<endl;
                break;
            }
            if(event.id == GPIOEVENT_EVENT_RISING_EDGE || event.id == GPIOEVENT_EVENT_FALLING_EDGE)
                callEventCallback();
        }
    }
    threadExitPromise.set_value_at_thread_exit();
}

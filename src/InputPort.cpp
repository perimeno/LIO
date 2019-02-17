#include "InputPort.h"
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <syslog.h>

using namespace std;

InputPort::InputPort(uint32_t pinNo):GPIO_Linux (pinNo){
    SetDirection(Direction::Input);
    fd=open(string(GetPinBasePath()+"value").c_str(),O_RDONLY | O_NONBLOCK);
    if(fd<0){
        syslog(LOG_ERR,"Unable to open input for polling: %d - %ud",fd,GetPinNo());
    }
    else{
        //a newly opened file consider changed, hence the seek and the read
        Read();
    }
}

InputPort::~InputPort(){
    if(fd>=0)
        close(fd);
}

void InputPort::SetTriggerEdge(InputPort::TriggerEdge edge){
    auto triggerEdge=make_unique<fstream>(GetPinBasePath()+"edge");
    if(!triggerEdge->good()){
        syslog(LOG_CRIT,"Unable to open edge descrriptor. - %ud",GetPinNo());
        throw runtime_error("Unable to open edge descrriptor.");
    }
    switch(edge){
        case TriggerEdge::None:
            *triggerEdge<<"none";
            break;
        case TriggerEdge::Rising:
            *triggerEdge<<"rising";
            break;
        case TriggerEdge::Falling:
            *triggerEdge<<"falling";
            break;
        case TriggerEdge::Both:
            *triggerEdge<<"both";
            break;
    }
}

bool InputPort::WaitForValidEvent(int timeout_ms){
    bool ret=false;
    if(fd>=0)
    {
        pollfd pollDescr;
        pollDescr.fd=fd;
        pollDescr.events=POLLPRI;
        int pret=poll(&pollDescr,1,timeout_ms);
        if(pret<0){
            cerr<<"Error during poll: "<<pret<<endl;
        }
        else if(pret==0)//timeout
            ;
        else
            ret=true;
    }
    return ret;
}

bool InputPort::Read(){
    if(fd>=0){
        lseek(fd, 0, SEEK_SET);
        char b[2];
        read(fd,b,2);
        return b[0]=='1';
    }
    else
        return ReadVal();
}

#include <string>
#include <sys/fcntl.h>
#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <sys/signal.h>
#include <sstream>

#include "InputSysfs.h"
#include <sys/epoll.h>

using namespace std;
InputSysfs::InputSysfs(uint32_t pinNo):sysfsWrapper(pinNo){
    sysfsWrapper.SetDirection(SysfsWrapper::Direction::Input);
     fd=open(string(sysfsWrapper.GetPinBasePath()+"value").c_str(),O_RDONLY | O_NONBLOCK);
     if(fd<0){
         cerr<<"Unable to open input for polling: "<<sysfsWrapper.GetPinNo()<<endl;
     }
     else{
         //a newly opened file consider changed, hence the seek and the read
         Read();
     }

}

InputSysfs::~InputSysfs(){
    if(fd>=0)
        close(fd);
}
void InputSysfs::SetTriggerEdge(TriggerEdge edge){
    auto triggerEdge=make_unique<fstream>(sysfsWrapper.GetPinBasePath()+"edge");
    if(!triggerEdge->good()){
        cerr<<"Unable to open edge descriptor. - "<<sysfsWrapper.GetPinNo()<<endl;
        throw runtime_error("Unable to open edge descriptor.");
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

void InputSysfs::SetPullUpDown(PullUpDown pud){
   switch (pud) {
   case PullUpDown::HiZ:
       sysfsWrapper.SetDirection(SysfsWrapper::Direction::Input);
       break;
   case PullUpDown::PullUp:
       sysfsWrapper.SetDirection(SysfsWrapper::Direction::High);
       break;
   case PullUpDown::PullDown:
       sysfsWrapper.SetDirection(SysfsWrapper::Direction::Low);
       break;
   }
}

bool InputSysfs::Read(){
    if(fd>=0){
        lseek(fd, 0, SEEK_SET);
        char b[2];
        read(fd,b,2);
        return b[0]=='1';
    }
    else
        return sysfsWrapper.ReadVal();
}

uint32_t InputSysfs::GetPinNo(){
    return sysfsWrapper.GetPinNo();
}


void InputSysfs::listenerThreadRunnable(std::promise<void>&& threadExitPromise,int fileDescriptor)
{
    if(fileDescriptor>=0){
        int epollFd=epoll_create1(0);
        struct epoll_event epollEvent{};
        epollEvent.events=EPOLLET;
        epollEvent.data.fd=fileDescriptor;
        if(epollFd>=0){
            if(epoll_ctl(epollFd,EPOLL_CTL_ADD,fileDescriptor,&epollEvent)>=0){
                while(!threadExitRequest){
                    if(epoll_wait(epollFd,&epollEvent,1,-1)==1)
                        callEventCallback();
                }
            }
            else
                cerr<<"epoll file control problem"<<endl;
            close(epollFd);
        }
        else
            cerr<<"epoll file creation problem"<<endl;
    }
    threadExitPromise.set_value_at_thread_exit();
}

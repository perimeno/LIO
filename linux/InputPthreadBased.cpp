#include "InputPthreadBased.h"
#include <thread>
#include <iostream>
#include <sys/signal.h>
#include <poll.h>
#include <sys/epoll.h>
#include <unistd.h>

using namespace std;
InputPthreadBased::InputPthreadBased():fd{-1},threadExitRequest{false},threadState{listenerThreadState::stopped}
{
}


void InputPthreadBased::StartListening(){
    if(threadState==listenerThreadState::stopped){
        std::promise<void> p;
        exitPerformed=p.get_future();
        thread t(bind(&InputPthreadBased::listenerThreadRunnable,this,placeholders::_1,placeholders::_2),move(p),fd);
        threadNativeId=t.native_handle();
        threadState=listenerThreadState::started;
        t.detach();
    }
    else
        cout<<"Listener thread already started for input pin "<<GetPinNo()<<"!"<<endl;
}

void InputPthreadBased::StopListening(){
    if(threadState==listenerThreadState::started){
        threadExitRequest=true;
        pthread_kill(threadNativeId,SIGINT);
        while(exitPerformed.wait_for(10ms)!=future_status::ready){
            pthread_kill(threadNativeId,SIGINT);
        }
        threadState=listenerThreadState::stopped;
    }
}


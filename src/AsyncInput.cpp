#include "AsyncInput.h"
#include <functional>
#include <iostream>
#include <syslog.h>

using namespace std;


AsyncInput::AsyncInput(uint32_t portNo):inputPort(portNo),exit(false){

}

void AsyncInput::Init(){
    inputPort.SetTriggerEdge(InputPort::TriggerEdge::Both);
    OffEvent();
    if(inputPort.Read())
        OnEvent();
}

void AsyncInput::Listen(){
    syslog(LOG_INFO,"Thread started for input %u",inputPort.GetPinNo());
    while(1){
        bool validEvent=inputPort.WaitForValidEvent();
        {
            volatile unique_lock<mutex>l(mutExit);
            if(exit)
                break;
        }
        if(validEvent){
            if(inputPort.Read())
                OnEvent();
            else
                OffEvent();
        }
    }
    syslog(LOG_INFO,"Thread end for input %u",inputPort.GetPinNo());
    condExit.notify_all();
}

void AsyncInput::StartListening(){
    listenigThread=std::thread(bind(&AsyncInput::Listen,this));
}

void AsyncInput::StopListening(){
    unique_lock<mutex>l(mutExit);
    exit=true;
    condExit.wait(l);
    listenigThread.join();
}

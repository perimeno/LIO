#include "SoftTimer.h"
#include <thread>
#include <functional>
#include <chrono>
using namespace LIO;
using namespace std;
SoftTimer::SoftTimer():repMode(repeatMode::single),myState(state::idle),
timerThreadExitRequest(false){
    promise<void> exitPromise;
    timerThreadFuture=exitPromise.get_future();
    thread(bind(&SoftTimer::timerTask,this,placeholders::_1),move(exitPromise)).detach();//start thread
    StopAndReset();
}

SoftTimer::~SoftTimer(){
    timerThreadExitRequest=true;
    s.signal();
    while(timerThreadFuture.wait_for(100ms)!=future_status::ready){
        s.signal();
    }
}

void SoftTimer::SetTimeout(std::chrono::milliseconds timeout){
    this->timeout=timeout;
}

void SoftTimer::Start(){
    if(myState==state::idle){
        myState=state::running;
        s.signal();
    }
}

void SoftTimer::StopAndReset(){
    if(myState==state::running){
        myState=state::idle;
        s.signal();
    }
}

void SoftTimer::SetRepeatMode(BasicTimer::repeatMode newRepMode){
    repMode=newRepMode;
}

void SoftTimer::timerTask(std::promise<void> &&exitPromise){
    while(!timerThreadExitRequest){
        switch(myState){
            case state::idle:{
                s.wait();
                break;
            }
            case state::running:{
                if(s.wait_for(timeout.load())==MySignal::sig_status::timeout){
                    timeoutCallback();
                    switch(repMode){
                        case repeatMode::single:
                            myState=state::idle;
                            break;
                        case repeatMode::continuous:
                            break;
                    }
                }
                break;
            }
        }
    }
    exitPromise.set_value_at_thread_exit();
}

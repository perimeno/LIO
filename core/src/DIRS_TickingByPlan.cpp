#include "DIRS_TickingByPlan.h"
#include <condition_variable>

using namespace std;
using namespace LIO;
DIRS_TickingByPlan::DIRS_TickingByPlan(BasicTimer& timer)
    :timer(timer),repState(repeatState::firstExecution),actualStrategy(repeatStrategy.end()){
    timer.SetRepeatMode(BasicTimer::repeatMode::continuous);
    timer.SetTimeoutCallback(bind(&DIRS_TickingByPlan::callOnCbIfPossible,this));
}

DIRS_TickingByPlan::~DIRS_TickingByPlan(){
    timer.StopAndReset();

}

void DIRS_TickingByPlan::handleOnEvent(){
    if(repState==repeatState::firstExecution){
        repState=repeatState::normal;
        callOnCbIfPossible();
    }
    timer.Start();
}

void DIRS_TickingByPlan::handleOffEvent(){
    repState=repeatState::firstExecution;
    timer.StopAndReset();
    offCb();
}

void DIRS_TickingByPlan::setRepeatStrategy(std::list<DIRS_TickingByPlan::RepeatInfo> strategy){
    repState=repeatState::firstExecution;
    timer.StopAndReset();
    unique_lock<mutex> lck(repeatStrategyMutex);
    repeatStrategy=strategy;
    actualStrategy=repeatStrategy.begin();

}

void DIRS_TickingByPlan::callOnCbIfPossible(){
    unique_lock<mutex> lck(repeatStrategyMutex);
    bool exit=false;
    while(actualStrategy!=repeatStrategy.end()){
        if(actualStrategy->multiplier == 0){
            ++actualStrategy;
            continue;
        }
        timer.SetTimeout(actualStrategy->interval);
        if(exit)
            break;
        if(actualStrategy->multiplier > 0){
            --(actualStrategy->multiplier);
            onCb();
            exit=true;
        }
    }
}







#include "DebouncerStrategyImpulseRepeat.h"
#include <condition_variable>

using namespace std;
using namespace LIO;
DebouncerStrategyImpulseRepeat::DebouncerStrategyImpulseRepeat(BasicTimer& timer)
    :timer(timer),repState(repeatState::firstExecution),actualStrategy(repeatStrategy.end()){
    timer.SetRepeatMode(BasicTimer::repeatMode::continuous);
    timer.SetTimeoutCallback(bind(&DebouncerStrategyImpulseRepeat::callOnCbIfPossible,this));
}

DebouncerStrategyImpulseRepeat::~DebouncerStrategyImpulseRepeat(){
    timer.StopAndReset();

}

void DebouncerStrategyImpulseRepeat::handleOnEvent(){
    if(repState==repeatState::firstExecution){
        repState=repeatState::normal;
        callOnCbIfPossible();
    }
    timer.Start();
}

void DebouncerStrategyImpulseRepeat::handleOffEvent(){
    repState=repeatState::firstExecution;
    timer.StopAndReset();
    offCb();
}

void DebouncerStrategyImpulseRepeat::setRepeatStrategy(std::list<DebouncerStrategyImpulseRepeat::RepeatInfo> strategy){
    repState=repeatState::firstExecution;
    timer.StopAndReset();
    unique_lock<mutex> lck(repeatStrategyMutex);
    repeatStrategy=strategy;
    actualStrategy=repeatStrategy.begin();

}

void DebouncerStrategyImpulseRepeat::callOnCbIfPossible(){
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







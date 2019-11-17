#include "Debouncer.h"
#include <functional>
#include <iostream>
using namespace std;
using namespace LIO;
Debouncer::Debouncer(BasicTimer& timer):debouncerStrategy(nullptr),timer(timer),myState{State::off},timerMode{TimerMode::initial}{
}
Debouncer::~Debouncer(){
}
void Debouncer::off(){
    if(timerMode==TimerMode::on||timerMode==TimerMode::initial){
        timerMode=TimerMode::off;
        timer.StopAndReset();
        timer.SetTimeoutCallback(bind(&Debouncer::offcb, this));
        timer.Start();
    }
}
void Debouncer::on(){
    if(timerMode==TimerMode::off||timerMode==TimerMode::initial){
        timerMode=TimerMode::on;
        timer.StopAndReset();
        timer.SetTimeoutCallback(bind(&Debouncer::oncb, this));
        timer.Start();
    }
}
void Debouncer::setDebounceInterval(std::chrono::milliseconds interv){
    timer.SetTimeout(interv);
}

void Debouncer::setStrategy(DebouncerStrategy * strategy){
    volatile unique_lock<mutex>lck(strategyMutex);
    debouncerStrategy=strategy;
}

void Debouncer::oncb(){
    if(myState==State::off){
        myState=State::on;
        volatile unique_lock<mutex>lck(strategyMutex);
        if(debouncerStrategy)
            debouncerStrategy->handleOnEvent();
    }
}

void Debouncer::offcb(){
    if(myState==State::on){
        myState=State::off;
        volatile unique_lock<mutex>lck(strategyMutex);
        if(debouncerStrategy)
            debouncerStrategy->handleOffEvent();
    }
}















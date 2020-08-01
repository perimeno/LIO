#include "DIRS_FixPeriodTicking.h"
#include <functional>

using namespace LIO;

DIRS_FixPeriodTicking::DIRS_FixPeriodTicking(LIO::BasicTimer &timer, std::chrono::milliseconds interval)
    :timer(timer), interval(interval){
    timer.StopAndReset();
    timer.SetTimeout(interval);
    timer.SetRepeatMode(BasicTimer::repeatMode::continuous);
    timer.SetTimeoutCallback(std::bind(&DIRS_FixPeriodTicking::timeoutCb,this));//intentionally this, because onCb can be modified by base object and timer object stores the (old) reference of it
}
DIRS_FixPeriodTicking::~DIRS_FixPeriodTicking(){
    timer.StopAndReset();
}

void DIRS_FixPeriodTicking::timeoutCb(){
    onCb();
}

void DIRS_FixPeriodTicking::handleOnEvent(){
    onCb();
    timer.Start();
}

void DIRS_FixPeriodTicking::handleOffEvent(){
    offCb();
    timer.StopAndReset();
}


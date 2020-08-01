#include "DebouncedInput.h"


using namespace LIO;

DebouncedInput::DebouncedInput(InputPin& port,
                                BasicTimer& timer,
                                std::chrono::milliseconds debounceDuration):
    DebouncedInput(port,timer,defaultStrategy,debounceDuration){
}

DebouncedInput::DebouncedInput(InputPin &port,
                               BasicTimer &timer,
                               DebouncerImpulseRepeatStrategy &DIRS_strategy,
                               std::chrono::milliseconds debounceDuration):
    inputPort(port),debouncer(timer),strategy(DIRS_strategy){
    debouncer.setStrategy(&strategy);
    debouncer.setDebounceInterval(debounceDuration);
    inputPort.SetEventCallback(bind(&DebouncedInput::inputEventProcessor,this,std::placeholders::_1));
    inputPort.StartListening();
}

DebouncedInput::~DebouncedInput(){
    inputPort.StopListening();
}

void DebouncedInput::setOnCallback(std::function<void()>onCallback){
    strategy.setOnCallback(onCallback);
}

void DebouncedInput::setOffCallback(std::function<void()>offCallback){
    strategy.setOffCallback(offCallback);
}
void DebouncedInput::inputEventProcessor(bool res){
    if(res)
        debouncer.on();
    else
        debouncer.off();
}


#ifndef DEBOUNCEDINPUT_H
#define DEBOUNCEDINPUT_H

#include <functional>
#include <chrono>
#include <cstdint>

#include "InputPin.h"
#include "Debouncer.h"
#include "DIRS_JustOneTick.h"

namespace LIO {
template <typename TDebouncerStrategy=DIRS_JustOneTick>
/**
 * @brief The purpose of this class to debounce a raw input pin data asynchronously. It uses
 * TDebouncerStrategy to determine how should it operate after an event occurred.
 * The class wires the debouncer logic and the input pin together and wraps input pin
 * event callback.
 */
class DebouncedInput
{
private:
    InputPin& inputPort;
    Debouncer debouncer;
    TDebouncerStrategy strategy;
    void inputEventProcessor(bool res){
        if(res)
            debouncer.on();
        else
            debouncer.off();
    }
public:
    /**
     * @brief Creates a debouncer entity
     * @param port InputPin that should be debounced
     * @param timer implementation of a timer that could be used by the debouncer
     * @param debounceDuration duration while input pin should be stable
     */
    DebouncedInput(InputPin& port,
                   BasicTimer& timer,
                   std::chrono::milliseconds debounceDuration=std::chrono::milliseconds(100)):
    inputPort(port),
    debouncer(timer){
        debouncer.setStrategy(&strategy);
        debouncer.setDebounceInterval(debounceDuration);
        inputPort.SetEventCallback(bind(&DebouncedInput::inputEventProcessor,this,std::placeholders::_1));
        inputPort.StartListening();
    }
    virtual ~DebouncedInput(){
        inputPort.StopListening();
    }
    /**
     * @brief Set the callback that should be called if a 0->1 event happened
     * @param onCallback
     */
    void setOnCallback(std::function<void()>onCallback){
        strategy.setOnCallback(onCallback);
    }
    /**
     * @brief Set the callback that should be called if a 1->0 event happened
     * @param offCallback
     */
    void setOffCallback(std::function<void()>offCallback){
        strategy.setOffCallback(offCallback);
    }
};
}
#endif // DEBOUNCEDLISTENER_H

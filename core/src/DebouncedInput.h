#ifndef DEBOUNCEDINPUT_H
#define DEBOUNCEDINPUT_H

#include <functional>
#include <chrono>
#include <cstdint>

#include "InputPin.h"
#include "Debouncer.h"
#include "DebouncerImpuseRepeatStrategy.h"
#include "DIRS_JustOneTick.h"

namespace LIO {
/**
 * @brief The purpose of this class to debounce a raw input pin data asynchronously. It uses
 * TDebouncerStrategy to determine how should it operate after an event occurred.
 * The class wires the debouncer logic and the input pin together and wraps input pin
 * event callback.
 */
class DebouncedInput
{
public:
    /**
     * @brief Creates a debouncer entity
     * @param port InputPin that should be debounced
     * @param timer implementation of a timer that could be used by the debouncer
     * @param debounceDuration duration while input pin should be stable
     */
    DebouncedInput(InputPin& port,
                   BasicTimer& timer,
                   std::chrono::milliseconds debounceDuration=std::chrono::milliseconds(50));
    DebouncedInput(InputPin& port,
                   BasicTimer& timer,
                   DebouncerImpulseRepeatStrategy& DIRS_strategy,
                   std::chrono::milliseconds debounceDuration=std::chrono::milliseconds(50));
    virtual ~DebouncedInput();
    /**
     * @brief Set the callback that should be called if a 0->1 event happened
     * @param onCallback
     */
    void setOnCallback(std::function<void()>onCallback);
    /**
     * @brief Set the callback that should be called if a 1->0 event happened
     * @param offCallback
     */
    void setOffCallback(std::function<void()>offCallback);
private:
    InputPin& inputPort;
    Debouncer debouncer;
    DebouncerImpulseRepeatStrategy& strategy;
    DIRS_JustOneTick defaultStrategy;
    void inputEventProcessor(bool res);
    void init();
};
}
#endif // DEBOUNCEDLISTENER_H

#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <chrono>
#include <cstdint>
#include <mutex>
#include <atomic>

#include "DebouncerStrategy.h"
#include "BasicTimer.h"

/**
 *  @brief This class implements a debouncer logic
*/
class Debouncer{

private:
    enum class State{off, on};
    enum class TimerMode{off, on, initial};
    DebouncerStrategy* debouncerStrategy;
    BasicTimer& timer;
    std::mutex strategyMutex;
    void debouncer();
    std::atomic<State> myState;
    TimerMode timerMode;
    void oncb();
    void offcb();
public:
    /**
     * @brief Creates a debouncer logic
     * @param timer
     */
    Debouncer(BasicTimer& timer);
    ~Debouncer();
    /**
     * @brief set debounce interval. This is the time while input should be stable.
     * @param interv
     */
    void setDebounceInterval(std::chrono::milliseconds interv);

    /**
     * @brief Deterines how should debouncer handle the stream of events
     * @param strategy
     */
    void setStrategy(DebouncerStrategy* strategy);

    /**
     * @brief raw 1->0 event handle
     */
    void off();

    /**
     * @brief raw 0->1 event handle
     */
    void on();

};

#endif

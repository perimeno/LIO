#ifndef DEBOUNCESSTRATEGYIMPULSEREPEAT_H
#define DEBOUNCESSTRATEGYIMPULSEREPEAT_H
#include "DebouncerStrategy.h"
#include <chrono>
#include <list>
#include <mutex>
#include <atomic>
#include <BasicTimer.h>

/**
 * @brief This strategy emits event according to the determined repeat
 * strategy in case of vald 1 input
 */
class DebouncerStrategyImpulseRepeat : public DebouncerStrategy
{

public:
    /**
     * @brief The RepeatInfo one elemnt of the repeat strategy
     */
    struct RepeatInfo{
        /**
         * @brief interval determines how much time shoud be elapsed BEFORE event happens
         */
        std::chrono::milliseconds interval;

        /**
         * @brief multiplier determines how many times should the system repeat the current element
         */
        uint32_t multiplier;
    };
    DebouncerStrategyImpulseRepeat(BasicTimer& timer);
    virtual ~DebouncerStrategyImpulseRepeat()override;
    virtual void handleOnEvent() override;
    virtual void handleOffEvent() override;
    /**
     * @brief You can set here the Repeat strategy. Each node of the list will be processed once,
     * but a node execution determined by its multiplier At he end of the list
     * system assumes that the strategy is compeared and stop emiting other events.
     *
     * i.e.: stratege{{100ms, 3x},{2ms,2x},{1ms, 1x}} means system will emit the following events:
     * ---input goes to valid state
     * ---0ms---event---100ms---event---100ms---event
     * ---2ms---event---2ms---event
     * ---1ms---event---no more event until the next valid 0->1 transition
     * @param strategy
     */
    void setRepeatStrategy(std::list<RepeatInfo>strategy);

private:
    enum class repeatState{firstExecution, normal};
    BasicTimer& timer;
    std::mutex repeatStrategyMutex;
    repeatState repState;
    std::list<RepeatInfo> repeatStrategy;
    std::list<RepeatInfo>::iterator actualStrategy;
    void callOnCbIfPossible();
};

#endif // DEBOUNCESSTRATEGYIMPULSEREPEAT_H

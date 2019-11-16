#ifndef DEBOUNCERSTRATEGYCBONLYONCE_H
#define DEBOUNCERSTRATEGYCBONLYONCE_H
#include "DebouncerStrategy.h"

/**
 * @brief This strategy emits only one event regardles the length
 * of valid 1 input. if input goes back to 0 it will emit another event
 * if it reaces valid 1 state
 */
class DebouncerStrategyCbOnlyOnce : public DebouncerStrategy
{
private:
    enum class state{off, on};
    state myState{state::off};
public:
    virtual void handleOnEvent() override;
    virtual void handleOffEvent() override;
};


#endif // DEBOUNCERSTRATEGYCBONLYONCE_H

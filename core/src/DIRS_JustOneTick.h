#ifndef DIRS_JUSTONETICK_H
#define DIRS_JUSTONETICK_H
#include "DebouncerImpuseRepeatStrategy.h"
namespace LIO {
/**
 * @brief This strategy emits only one event regardles the length
 * of valid 1 input. if input goes back to 0 it will emit another event
 * if it reaces valid 1 state
 */
class DIRS_JustOneTick : public DebouncerImpulseRepeatStrategy
{
private:
    enum class state{off, on};
    state myState{state::off};
public:
    virtual void handleOnEvent() override;
    virtual void handleOffEvent() override;
};
}

#endif // DIRS_JUSTONETICK_H

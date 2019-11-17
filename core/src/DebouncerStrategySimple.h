#ifndef DEBOUNCESSTRATEGYSIMPLE_H
#define DEBOUNCESSTRATEGYSIMPLE_H
#include "DebouncerStrategy.h"
namespace LIO {
/**
 * @brief This strategy simple path the valid input to valid output
 * i.e. valid 0->1 transmission and after that login 1 input events
 * are emitted accoding to the timer operation. if it is seingle,
 * only one event will be emitted, if the mode is continuous
 * events are emitted on every timer overflow
 */
class DebouncerStrategySimple:public DebouncerStrategy
{
public:
    virtual void handleOnEvent() override;
    virtual void handleOffEvent() override;
};
}


#endif // DEBOUNCESSTRATEGYSIMPLE_H

#include "DebouncerStrategySimple.h"

void DebouncerStrategySimple::handleOnEvent(){
    onCb();
}

void DebouncerStrategySimple::handleOffEvent(){
    offCb();
}



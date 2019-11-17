#include "DebouncerStrategySimple.h"
using namespace LIO;
void DebouncerStrategySimple::handleOnEvent(){
    onCb();
}

void DebouncerStrategySimple::handleOffEvent(){
    offCb();
}



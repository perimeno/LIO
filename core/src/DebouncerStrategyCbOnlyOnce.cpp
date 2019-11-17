#include "DebouncerStrategyCbOnlyOnce.h"

using namespace LIO;
void DebouncerStrategyCbOnlyOnce::handleOnEvent(){
    if(onCb && myState==state::off){
        onCb();
        myState=state::on;
    }
}

void DebouncerStrategyCbOnlyOnce::handleOffEvent(){
    if(offCb && myState==state::on){
        offCb();
        myState=state::off;
    }
}

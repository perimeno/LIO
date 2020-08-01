#include "DIRS_JustOneTick.h"

using namespace LIO;
void DIRS_JustOneTick::handleOnEvent(){
    if(onCb && myState==state::off){
        onCb();
        myState=state::on;
    }
}

void DIRS_JustOneTick::handleOffEvent(){
    if(offCb && myState==state::on){
        offCb();
        myState=state::off;
    }
}

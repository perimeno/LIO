#include "InputPin.h"

using namespace std;

InputPin::InputPin():eventCb(bind(&InputPin::dummyCb,this)){
}
void InputPin::SetEventCallback(std::function<void (bool)> cb){
    unique_lock<mutex>lck(eventCbMutex);
    eventCb=cb;
}

void InputPin::RemoveEventCallback(){
    unique_lock<mutex>lck(eventCbMutex);
    eventCb=bind(&InputPin::dummyCb,this);
}
void InputPin::dummyCb(){

}

void InputPin::callEventCallback(){
    unique_lock<mutex>lck(eventCbMutex);
    eventCb(Read());
}

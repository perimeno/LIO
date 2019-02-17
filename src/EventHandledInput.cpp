#include "EventHandledInput.h"

EventHandledInput::EventHandledInput(){

}

void EventHandledInput::OnEvent(){
    if(onCallback!=nullptr)
        onCallback();
}

void EventHandledInput::OffEvent(){
    if(offCallback!=nullptr)
        offCallback();
}

void EventHandledInput::SetOnCallback(std::function<void ()>callback){
    onCallback=callback;
}

void EventHandledInput::SetOffCallback(std::function<void ()>callback){
    offCallback=callback;
}

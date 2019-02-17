#pragma once
#include <EventHandledInput.h>
class EventHandledInput4Test: public EventHandledInput{
public:
    virtual ~EventHandledInput4Test()=default;
    virtual void TriggerOnEvent(){
        OnEvent();
    }

    virtual void TriggerOffEvent(){
        OffEvent();
    }
};

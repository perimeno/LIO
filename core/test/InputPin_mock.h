#pragma once
#include <gmock/gmock.h>
#include "InputPin.h"

class InputPin_mock : public InputPin{
public:
    MOCK_METHOD1(SetTriggerEdge,void(TriggerEdge edge));
    MOCK_METHOD1(SetPullUpDown, void(PullUpDown pud));
    MOCK_METHOD0(Read,bool());
    MOCK_METHOD0(StartListening,void());
    MOCK_METHOD0(StopListening,void());
    MOCK_METHOD0(GetPinNo,uint32_t());
    void explicitEventCallback(){
        callEventCallback();
    }
};

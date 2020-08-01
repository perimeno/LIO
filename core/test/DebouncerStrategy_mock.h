#pragma once
#include <gmock/gmock.h>
#include <DebouncerImpuseRepeatStrategy.h>

class DebouncerStrategy_mock:public LIO::DebouncerImpulseRepeatStrategy{
public:
    MOCK_METHOD0(handleOffEvent,void ());
    MOCK_METHOD0(handleOnEvent,void());
    void explicitOnCb(){
        onCb();
    }
    void explicitOffCb(){
        offCb();
    }
};

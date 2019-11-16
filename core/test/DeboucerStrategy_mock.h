#pragma once
#include <gmock/gmock.h>
#include <DebouncerStrategy.h>

class DeboucerStrategy_mock:public DebouncerStrategy{
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

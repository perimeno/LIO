#pragma once
#include <gmock/gmock.h>
#include <BasicTimer.h>
class BasicTimerMock:public BasicTimer{

    // IBasicTimer interface
public:
   MOCK_METHOD1(SetTimeout,void(std::chrono::milliseconds));
   MOCK_METHOD0(Start,void());
   MOCK_METHOD0(StopAndReset,void());
   MOCK_METHOD1(SetRepeatMode,void(repeatMode));
   void explicitCallTimeoutCb(){
       timeoutCallback();
   }
};


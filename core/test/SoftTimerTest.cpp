#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include <future>

#include "SoftTimer.h"

using namespace std;
using testing::Return;

ACTION_P(SignalCallback,promise){
    promise->set_value();
}

class SoftTimerTest:public testing::Test{
public:
    MOCK_METHOD0(timeoutCallback,void());
    SoftTimer subject;
    promise<void> timerElapsedPromise;
    future<void> timerElapsed;
    SoftTimerTest():timerElapsed(timerElapsedPromise.get_future()){
        ON_CALL(*this,timeoutCallback()).WillByDefault(SignalCallback(&timerElapsedPromise));
    }
};
TEST_F(SoftTimerTest,TimeoutWithoutCallback_NoProblem){
    subject.SetTimeout(1ms);
    subject.Start();
    this_thread::sleep_for(100ms);
}
TEST_F(SoftTimerTest,TimeoutWithCallback_ProperTiming){
    EXPECT_CALL(*this,timeoutCallback).Times(1);
    subject.SetTimeout(10ms);
    subject.SetTimeoutCallback(bind(&SoftTimerTest::timeoutCallback,this));
    auto start=chrono::steady_clock::now();
    subject.Start();
    timerElapsed.wait();
    auto stop=chrono::steady_clock::now();
    ASSERT_LT(stop-start,1s);
    ASSERT_GT(stop-start,10ms);
}
TEST_F(SoftTimerTest,NoTimeout_NoCallback){
    EXPECT_CALL(*this,timeoutCallback).Times(0);
    subject.SetTimeout(10ms);
    subject.SetTimeoutCallback(bind(&SoftTimerTest::timeoutCallback,this));
    subject.Start();
    this_thread::sleep_for(5ms);
    subject.StopAndReset();
    auto ret=timerElapsed.wait_for(100ms);
    ASSERT_EQ(ret,future_status::timeout);
}
TEST_F(SoftTimerTest,TimeoutWithCallback_MultipleStart){
    EXPECT_CALL(*this,timeoutCallback).Times(1);
    subject.SetTimeout(10ms);
    subject.SetTimeoutCallback(bind(&SoftTimerTest::timeoutCallback,this));
    auto start=chrono::steady_clock::now();
    subject.Start();
    subject.Start();
    this_thread::sleep_for(5ms);
    subject.Start();
    subject.Start();
    timerElapsed.wait();
    auto stop=chrono::steady_clock::now();
    ASSERT_LT(stop-start,1s);
    ASSERT_GT(stop-start,10ms);
}
TEST_F(SoftTimerTest,TimeoutWithCallback_StartAfterTimeout){
    EXPECT_CALL(*this,timeoutCallback).Times(1).WillOnce(SignalCallback(&timerElapsedPromise));
    subject.SetTimeout(10ms);
    subject.SetTimeoutCallback(bind(&SoftTimerTest::timeoutCallback,this));
    subject.Start();
    timerElapsed.wait();
    promise<void> run2;
    timerElapsed=run2.get_future();
    EXPECT_CALL(*this,timeoutCallback).Times(1).WillOnce(SignalCallback(&run2));
    auto start=chrono::steady_clock::now();
    subject.Start();
    timerElapsed.wait();
    auto stop=chrono::steady_clock::now();
    ASSERT_LT(stop-start,1s);
    ASSERT_GT(stop-start,10ms);
}

TEST_F(SoftTimerTest,TimeoutWithCallback_changeTimingAfterTimeout){
    EXPECT_CALL(*this,timeoutCallback).Times(1).WillOnce(SignalCallback(&timerElapsedPromise));
    subject.SetTimeout(10ms);
    subject.SetTimeoutCallback(bind(&SoftTimerTest::timeoutCallback,this));
    subject.Start();
    timerElapsed.wait();
    promise<void> run2;
    timerElapsed=run2.get_future();
    EXPECT_CALL(*this,timeoutCallback).Times(1).WillOnce(SignalCallback(&run2));
    subject.SetTimeout(100ms);
    auto start=chrono::steady_clock::now();
    subject.Start();
    timerElapsed.wait();
    auto stop=chrono::steady_clock::now();
    ASSERT_LT(stop-start,1s);
    ASSERT_GT(stop-start,100ms);
}


TEST_F(SoftTimerTest,TimeoutWithCallback_ContinuousMode){
    EXPECT_CALL(*this,timeoutCallback).Times(1).WillOnce(SignalCallback(&timerElapsedPromise));
    subject.SetTimeout(10ms);
    subject.SetRepeatMode(BasicTimer::repeatMode::continuous);
    subject.SetTimeoutCallback(bind(&SoftTimerTest::timeoutCallback,this));
    subject.Start();
    timerElapsed.wait();
    promise<void> run2;
    timerElapsed=run2.get_future();
    EXPECT_CALL(*this,timeoutCallback).Times(1).WillOnce(SignalCallback(&run2));
    timerElapsed.wait();
    subject.StopAndReset();
}

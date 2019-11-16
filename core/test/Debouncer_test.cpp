#include <gmock/gmock.h>
#include <Debouncer.h>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <thread>

#include "BasicTimerMock.h"

#include "DeboucerStrategy_mock.h"


using namespace std;

class Debounce_test : public ::testing::Test{

public:
    BasicTimerMock timer;
    Debouncer subject{timer};
    DeboucerStrategy_mock strategy;
    virtual void SetUp()override{
        subject.setStrategy(&strategy);
    }

};
TEST_F(Debounce_test, debounceInterval){
    EXPECT_CALL(timer,SetTimeout(1ms));
    subject.setDebounceInterval(1ms);
}
TEST_F(Debounce_test, off){
    EXPECT_CALL(strategy,handleOffEvent()).Times(0);
    EXPECT_CALL(strategy,handleOnEvent()).Times(0);
    subject.off();
}
TEST_F(Debounce_test, partialOn){
    EXPECT_CALL(strategy,handleOffEvent()).Times(0);
    EXPECT_CALL(strategy,handleOnEvent()).Times(0);
    subject.off();
    subject.on();
    subject.off();
    subject.on();
}
TEST_F(Debounce_test, switchedOn){
    EXPECT_CALL(strategy,handleOffEvent()).Times(0);
    EXPECT_CALL(strategy,handleOnEvent()).Times(1);
    subject.off();
    subject.on();
    subject.off();
    subject.on();
    timer.explicitCallTimeoutCb();
}
TEST_F(Debounce_test, switchedOnAndOff){
    EXPECT_CALL(strategy,handleOffEvent()).Times(1);
    EXPECT_CALL(strategy,handleOnEvent()).Times(1);

    subject.on();
    timer.explicitCallTimeoutCb();
    subject.off();
    timer.explicitCallTimeoutCb();
}
TEST_F(Debounce_test, noiseOnLines_OffToOn){
    EXPECT_CALL(strategy,handleOffEvent()).Times(0);
    EXPECT_CALL(strategy,handleOnEvent()).Times(1);

    subject.on();
    subject.off();
    timer.explicitCallTimeoutCb();
    subject.on();
    subject.off();
    subject.on();
    timer.explicitCallTimeoutCb();
}
TEST_F(Debounce_test, noiseOnLines_OnToOff){
    subject.on();
    timer.explicitCallTimeoutCb();
    EXPECT_CALL(strategy,handleOffEvent()).Times(1);
    EXPECT_CALL(strategy,handleOnEvent()).Times(0);
    subject.off();
    subject.on();
    timer.explicitCallTimeoutCb();
    subject.off();
    subject.on();
    subject.off();
    timer.explicitCallTimeoutCb();
}
TEST_F(Debounce_test, noiseOnLines_stress){
    EXPECT_CALL(strategy,handleOffEvent()).Times(1);
    EXPECT_CALL(strategy,handleOnEvent()).Times(1);

    subject.on();
    subject.off();
    subject.on();
    timer.explicitCallTimeoutCb();
    subject.off();
    subject.on();
    timer.explicitCallTimeoutCb();
    subject.off();
    subject.on();
    subject.off();
    timer.explicitCallTimeoutCb();
}



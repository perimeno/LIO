#include <gmock/gmock.h>
#include <DIRS_FixPeriodTicking.h>
#include <Debouncer.h>
#include <future>
#include "BasicTimerMock.h"
using namespace std;
using namespace LIO;

class DIRS_FixPeriodTickingTest: public testing::Test{
public:
    BasicTimerMock timer;
    DIRS_FixPeriodTicking subject{timer,1s};
    MOCK_METHOD0(onCallback,void());
    MOCK_METHOD0(offCallback,void());
protected:
    virtual void SetUp() override;
};

void DIRS_FixPeriodTickingTest::SetUp(){
    subject.setOnCallback(bind(&DIRS_FixPeriodTickingTest::onCallback,this));
    subject.setOffCallback(bind(&DIRS_FixPeriodTickingTest::offCallback,this));
}
TEST(DIRS_TickingTest_inint,withoutCallbacks){
    BasicTimerMock timer_debouncer;
    BasicTimerMock timer_repeat;
    Debouncer debouncer(timer_debouncer);
    EXPECT_CALL(timer_repeat,StopAndReset());
    EXPECT_CALL(timer_repeat,SetTimeout(1000ms));
    EXPECT_CALL(timer_repeat,SetRepeatMode(BasicTimer::repeatMode::continuous));
    DIRS_FixPeriodTicking subject(timer_repeat,1000ms);
    debouncer.setStrategy(&subject);
    EXPECT_CALL(timer_repeat,StopAndReset());
    timer_debouncer.explicitCallTimeoutCb();
}
TEST_F(DIRS_FixPeriodTickingTest,On){
    EXPECT_CALL(*this,offCallback()).Times(0);
    EXPECT_CALL(*this,onCallback()).Times(1);
    subject.handleOnEvent();
}
TEST_F(DIRS_FixPeriodTickingTest,Off){
    EXPECT_CALL(*this,onCallback()).Times(0);
    EXPECT_CALL(*this,offCallback()).Times(1);
    subject.handleOffEvent();
}
TEST_F(DIRS_FixPeriodTickingTest,On_multipleInpulse){
    EXPECT_CALL(*this,offCallback()).Times(0);
    EXPECT_CALL(*this,onCallback()).Times(1);
    timer.explicitCallTimeoutCb();
    EXPECT_CALL(*this,offCallback()).Times(0);
    EXPECT_CALL(*this,onCallback()).Times(1);
    timer.explicitCallTimeoutCb();
    EXPECT_CALL(*this,offCallback()).Times(0);
    EXPECT_CALL(*this,onCallback()).Times(1);
    timer.explicitCallTimeoutCb();
}

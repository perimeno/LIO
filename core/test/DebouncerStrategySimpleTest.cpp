#include <gmock/gmock.h>
#include <DebouncerStrategySimple.h>
#include <Debouncer.h>
#include <future>
#include "BasicTimerMock.h"
using namespace std;
using namespace LIO;

class DebouncerStrategySimpleTest: public testing::Test{
public:
    DebouncerStrategySimple subject;
    MOCK_METHOD0(onCallback,void());
    MOCK_METHOD0(offCallback,void());
protected:
    virtual void SetUp() override;
};

void DebouncerStrategySimpleTest::SetUp(){
    subject.setOnCallback(bind(&DebouncerStrategySimpleTest::onCallback,this));
    subject.setOffCallback(bind(&DebouncerStrategySimpleTest::offCallback,this));
}
TEST(DebouncerStrategySimpleTest_inint,withoutCallbacks){
    BasicTimerMock timer;
    Debouncer debouncer(timer);
    DebouncerStrategySimple subject;
    debouncer.setStrategy(&subject);
    timer.explicitCallTimeoutCb();
}
TEST_F(DebouncerStrategySimpleTest,On){
    EXPECT_CALL(*this,offCallback()).Times(0);
    EXPECT_CALL(*this,onCallback()).Times(1);
    subject.handleOnEvent();
}
TEST_F(DebouncerStrategySimpleTest,Off){
    EXPECT_CALL(*this,onCallback()).Times(0);
    EXPECT_CALL(*this,offCallback()).Times(1);
    subject.handleOffEvent();
}

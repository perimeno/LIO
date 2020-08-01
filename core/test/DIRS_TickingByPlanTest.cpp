#include <gmock/gmock.h>
#include <DIRS_TickingByPlan.h>
#include <Debouncer.h>
#include <SoftTimer.h>
using namespace std;
using namespace LIO;

class DIRS_TickingByPlanTest: public testing::Test{
public:
    SoftTimer timer_debouncer;
    SoftTimer timer_strategy;
    DIRS_TickingByPlan subject{timer_strategy};
    Debouncer debouncer{timer_debouncer};
    MOCK_METHOD0(onCallback,void());
    MOCK_METHOD0(offCallback,void());
    // Test interface
protected:
    virtual void SetUp() override;
};

void DIRS_TickingByPlanTest::SetUp(){
    subject.setOnCallback(bind(&DIRS_TickingByPlanTest::onCallback,this));
    subject.setOffCallback(bind(&DIRS_TickingByPlanTest::offCallback,this));
    debouncer.setStrategy(&subject);
    debouncer.setDebounceInterval(1ms);
}
TEST_F(DIRS_TickingByPlanTest,OnEmpty){
    EXPECT_CALL(*this,onCallback()).Times(0);
    EXPECT_CALL(*this,offCallback()).Times(0);
    debouncer.on();
    this_thread::sleep_for(5ms);
}
TEST_F(DIRS_TickingByPlanTest,OnOneItem){
    subject.setRepeatStrategy({{1ms,5}});
    EXPECT_CALL(*this,onCallback()).Times(5);
    EXPECT_CALL(*this,offCallback()).Times(0);
    debouncer.on();
    this_thread::sleep_for(100ms);
}
TEST_F(DIRS_TickingByPlanTest,Interval){
    subject.setRepeatStrategy({{200ms,3}});

    EXPECT_CALL(*this,onCallback()).Times(1);
    EXPECT_CALL(*this,offCallback()).Times(0);
    debouncer.on();
    this_thread::sleep_for(40ms);
    EXPECT_CALL(*this,onCallback()).Times(1);
    EXPECT_CALL(*this,offCallback()).Times(0);
    this_thread::sleep_for(240ms);
    EXPECT_CALL(*this,onCallback()).Times(1);
    EXPECT_CALL(*this,offCallback()).Times(0);
    this_thread::sleep_for(240ms);
    EXPECT_CALL(*this,onCallback()).Times(0);
    EXPECT_CALL(*this,offCallback()).Times(0);
    this_thread::sleep_for(400ms);
}

TEST_F(DIRS_TickingByPlanTest,MultipleItem){
    subject.setRepeatStrategy({{1ms,2},{100ms,3}});
    EXPECT_CALL(*this,onCallback()).Times(2);
    EXPECT_CALL(*this,offCallback()).Times(0);
    debouncer.on();
    this_thread::sleep_for(20ms);
    EXPECT_CALL(*this,onCallback()).Times(3);
    EXPECT_CALL(*this,offCallback()).Times(0);
    this_thread::sleep_for(400ms);
    EXPECT_CALL(*this,onCallback()).Times(0);
    EXPECT_CALL(*this,offCallback()).Times(0);
    this_thread::sleep_for(400ms);
}

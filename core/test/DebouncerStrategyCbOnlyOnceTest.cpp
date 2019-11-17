#include <gmock/gmock.h>
#include <DebouncerStrategyCbOnlyOnce.h>

using namespace std;
using namespace LIO;

class DebouncerStrategyCbOnlyOnceTest: public testing::Test{
public:
    DebouncerStrategyCbOnlyOnce subject;
    MOCK_METHOD0(onCb,void());
    MOCK_METHOD0(offCb,void());


    // Test interface
protected:
    virtual void SetUp() override;
};

void DebouncerStrategyCbOnlyOnceTest::SetUp(){
    subject.setOnCallback(bind(&DebouncerStrategyCbOnlyOnceTest::onCb,this));
    subject.setOffCallback(bind(&DebouncerStrategyCbOnlyOnceTest::offCb,this));
}

TEST_F(DebouncerStrategyCbOnlyOnceTest, multipleOnEventButOnOnCallback){
    EXPECT_CALL(*this,onCb()).Times(1);
    EXPECT_CALL(*this,offCb()).Times(0);
    subject.handleOnEvent();
    subject.handleOnEvent();
    subject.handleOnEvent();
    subject.handleOnEvent();
}
TEST_F(DebouncerStrategyCbOnlyOnceTest, multipleOffEventButOnOnCallback){
    EXPECT_CALL(*this,onCb()).Times(0);
    EXPECT_CALL(*this,offCb()).Times(0);
    subject.handleOffEvent();
    subject.handleOffEvent();
    subject.handleOffEvent();
}
TEST_F(DebouncerStrategyCbOnlyOnceTest, multipleOnOffEventOneOneCallback){
    EXPECT_CALL(*this,onCb()).Times(1);
    EXPECT_CALL(*this,offCb()).Times(1);
    subject.handleOffEvent();
    subject.handleOffEvent();
    subject.handleOffEvent();
    subject.handleOnEvent();
    subject.handleOnEvent();
    subject.handleOnEvent();
    subject.handleOffEvent();
    subject.handleOffEvent();
}
TEST_F(DebouncerStrategyCbOnlyOnceTest, oneOnOffEventOneOnOffCallback){
    EXPECT_CALL(*this,onCb()).Times(1);
    EXPECT_CALL(*this,offCb()).Times(1);
    subject.handleOnEvent();
    subject.handleOffEvent();
}

#include <gmock/gmock.h>
#include <DIRS_JustOneTick.h>

using namespace std;
using namespace LIO;

class DIRS_JustOneTickTest: public testing::Test{
public:
    DIRS_JustOneTick subject;
    MOCK_METHOD0(onCb,void());
    MOCK_METHOD0(offCb,void());


    // Test interface
protected:
    virtual void SetUp() override;
};

void DIRS_JustOneTickTest::SetUp(){
    subject.setOnCallback(bind(&DIRS_JustOneTickTest::onCb,this));
    subject.setOffCallback(bind(&DIRS_JustOneTickTest::offCb,this));
}

TEST_F(DIRS_JustOneTickTest, multipleOnEventButOnOnCallback){
    EXPECT_CALL(*this,onCb()).Times(1);
    EXPECT_CALL(*this,offCb()).Times(0);
    subject.handleOnEvent();
    subject.handleOnEvent();
    subject.handleOnEvent();
    subject.handleOnEvent();
}
TEST_F(DIRS_JustOneTickTest, multipleOffEventButOnOnCallback){
    EXPECT_CALL(*this,onCb()).Times(0);
    EXPECT_CALL(*this,offCb()).Times(0);
    subject.handleOffEvent();
    subject.handleOffEvent();
    subject.handleOffEvent();
}
TEST_F(DIRS_JustOneTickTest, multipleOnOffEventOneOneCallback){
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
TEST_F(DIRS_JustOneTickTest, oneOnOffEventOneOnOffCallback){
    EXPECT_CALL(*this,onCb()).Times(1);
    EXPECT_CALL(*this,offCb()).Times(1);
    subject.handleOnEvent();
    subject.handleOffEvent();
}

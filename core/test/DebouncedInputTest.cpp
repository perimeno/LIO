#include <gtest/gtest.h>

#include <DebouncedInput.h>

#include "InputPin_mock.h"
#include "BasicTimerMock.h"

using namespace std;
using testing::Return;
using namespace LIO;

class DebouncedInputTest : public testing::Test{
public:
    InputPin_mock input_mock;
    BasicTimerMock timerMock;
    DebouncedInput<> subject{input_mock,timerMock};
    MOCK_METHOD0(onCb,void());
    MOCK_METHOD0(offCb,void());
};

TEST_F(DebouncedInputTest,withoutCallback){
    EXPECT_CALL(input_mock,Read()).WillOnce(Return(true));
    input_mock.explicitEventCallback();
    timerMock.explicitCallTimeoutCb();
}
TEST_F(DebouncedInputTest,onCallback){

    subject.setOnCallback(bind(&DebouncedInputTest::onCb,this));
    subject.setOffCallback(bind(&DebouncedInputTest::offCb,this));
    EXPECT_CALL(input_mock,Read()).WillOnce(Return(true));
    EXPECT_CALL(*this,onCb()).Times(1);
    EXPECT_CALL(*this,offCb()).Times(0);
    input_mock.explicitEventCallback();
    timerMock.explicitCallTimeoutCb();

}
TEST_F(DebouncedInputTest,offCallback){

    subject.setOnCallback(bind(&DebouncedInputTest::onCb,this));
    subject.setOffCallback(bind(&DebouncedInputTest::offCb,this));
    EXPECT_CALL(input_mock,Read()).WillOnce(Return(true));
    input_mock.explicitEventCallback();
    timerMock.explicitCallTimeoutCb();
    EXPECT_CALL(*this,offCb()).Times(1);
    EXPECT_CALL(input_mock,Read()).WillOnce(Return(false));
    input_mock.explicitEventCallback();
    timerMock.explicitCallTimeoutCb();

}
TEST_F(DebouncedInputTest,oneInputEventMultipleTimeout){

    subject.setOnCallback(bind(&DebouncedInputTest::onCb,this));
    subject.setOffCallback(bind(&DebouncedInputTest::offCb,this));
    EXPECT_CALL(input_mock,Read()).WillOnce(Return(true));
    EXPECT_CALL(*this,onCb()).Times(1);
    EXPECT_CALL(*this,offCb()).Times(0);
    input_mock.explicitEventCallback();
    timerMock.explicitCallTimeoutCb();
    timerMock.explicitCallTimeoutCb();
    timerMock.explicitCallTimeoutCb();
    timerMock.explicitCallTimeoutCb();
    timerMock.explicitCallTimeoutCb();

}

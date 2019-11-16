#include <gtest/gtest.h>
#include "InputPin_mock.h"
#include <functional>

using namespace std;
using testing::Return;
class InputPinTest:public testing::Test{
public:
    InputPin_mock subject;
    MOCK_METHOD1(myCb,void(bool));
};
TEST_F(InputPinTest,defaultCallback){
    subject.explicitEventCallback();//No exception
}
TEST_F(InputPinTest, registerCallback){
    subject.SetEventCallback(bind(&InputPinTest::myCb,this,placeholders::_1));
    EXPECT_CALL(*this,myCb(testing::_)).Times(1);
    subject.explicitEventCallback();
}
TEST_F(InputPinTest, unEegisterCallback){
    subject.SetEventCallback(bind(&InputPinTest::myCb,this,placeholders::_1));
    subject.RemoveEventCallback();
    EXPECT_CALL(*this,myCb).Times(0);
    subject.explicitEventCallback();
}
TEST_F(InputPinTest, passReadValueToCallback){
    subject.SetEventCallback(bind(&InputPinTest::myCb,this,placeholders::_1));
    EXPECT_CALL(subject,Read()).WillOnce(Return(true));
    EXPECT_CALL(*this,myCb(true)).Times(1);
    subject.explicitEventCallback();
    EXPECT_CALL(subject,Read()).WillOnce(Return(false));
    EXPECT_CALL(*this,myCb(false)).Times(1);
    subject.explicitEventCallback();

}

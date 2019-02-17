#include <gmock/gmock.h>
#include <functional>
#include "EventHandledInput4Test.h"

using namespace std;

class mock_callback{
public:
    MOCK_METHOD0(testCallback,void());
};
class test_EventHandledInput:public testing::Test{
protected:
    EventHandledInput4Test input;
};
TEST_F(test_EventHandledInput,TurnOnCallback){
    testing::StrictMock<mock_callback> cb;
    input.TriggerOnEvent();
    input.SetOnCallback(bind(&mock_callback::testCallback,&cb));
    EXPECT_CALL(cb,testCallback).Times(1);
    input.TriggerOnEvent();
}
TEST_F(test_EventHandledInput,TurnOffCallback){
    testing::StrictMock<mock_callback> cb;
    input.TriggerOffEvent();
    input.SetOffCallback(bind(&mock_callback::testCallback,&cb));
    EXPECT_CALL(cb,testCallback).Times(1);
    input.TriggerOffEvent();
}
TEST_F(test_EventHandledInput,TurnOnOffCallback){
    volatile testing::InSequence dummy;
    testing::StrictMock<mock_callback> cb_on;
    testing::StrictMock<mock_callback> cb_off;
    input.SetOnCallback(bind(&mock_callback::testCallback,&cb_on));
    input.SetOffCallback(bind(&mock_callback::testCallback,&cb_off));
    EXPECT_CALL(cb_on,testCallback).Times(1);
    input.TriggerOnEvent();
    EXPECT_CALL(cb_off,testCallback).Times(1);
    input.TriggerOffEvent();
}

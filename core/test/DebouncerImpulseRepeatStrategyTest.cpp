#include<gtest/gtest.h>
#include "DebouncerStrategy_mock.h"

using namespace std;
using namespace LIO;

class DebounceStrategyTest : public testing::Test{
public:
    DebouncerStrategy_mock subject;
};

TEST_F(DebounceStrategyTest,withoutCallback){
    subject.explicitOnCb();
    subject.explicitOffCb();
}
TEST_F(DebounceStrategyTest,callbacks){
    EXPECT_CALL(subject,handleOnEvent()).Times(2);
    EXPECT_CALL(subject,handleOffEvent()).Times(1);
    subject.setOnCallback(bind(&DebouncerStrategy_mock::handleOnEvent,&subject));
    subject.setOffCallback(bind(&DebouncerStrategy_mock::handleOffEvent,&subject));
    subject.explicitOnCb();
    subject.explicitOnCb();
    subject.explicitOffCb();
}

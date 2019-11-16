#include<gtest/gtest.h>
#include "DeboucerStrategy_mock.h"

using namespace std;

class DebounceStrategyTest : public testing::Test{
public:
    DeboucerStrategy_mock subject;
};

TEST_F(DebounceStrategyTest,withoutCallback){
    subject.explicitOnCb();
    subject.explicitOffCb();
}
TEST_F(DebounceStrategyTest,callbacks){
    EXPECT_CALL(subject,handleOnEvent()).Times(2);
    EXPECT_CALL(subject,handleOffEvent()).Times(1);
    subject.setOnCallback(bind(&DeboucerStrategy_mock::handleOnEvent,&subject));
    subject.setOffCallback(bind(&DeboucerStrategy_mock::handleOffEvent,&subject));
    subject.explicitOnCb();
    subject.explicitOnCb();
    subject.explicitOffCb();
}

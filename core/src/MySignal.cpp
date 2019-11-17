#include "MySignal.h"
using namespace std;
using namespace LIO;
void MySignal::wait(){
    unique_lock<mutex>lck(m);
    c.wait(lck,[&]{return indicator;});
    indicator=false;
}

void MySignal::signal(){
    {
        unique_lock<mutex> lck(m);
        indicator=true;
    }
    c.notify_one();
}


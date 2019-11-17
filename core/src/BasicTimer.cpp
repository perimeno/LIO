#include <BasicTimer.h>
using namespace LIO;

BasicTimer::BasicTimer():timeoutCallback([]{}){

}

void BasicTimer::SetTimeoutCallback(std::function<void ()>cb){
    timeoutCallback=cb;
}

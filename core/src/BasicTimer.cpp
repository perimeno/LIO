#include <BasicTimer.h>


BasicTimer::BasicTimer():timeoutCallback([]{}){

}

void BasicTimer::SetTimeoutCallback(std::function<void ()>cb){
    timeoutCallback=cb;
}

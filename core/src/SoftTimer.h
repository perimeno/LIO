#ifndef SOFTTIMER_H
#define SOFTTIMER_H
#include <future>
#include <atomic>
#include <condition_variable>

#include "BasicTimer.h"
#include "MySignal.h"
namespace LIO {
/**
 * @brief SW implementation of a basicTimer
 */
class SoftTimer:public BasicTimer{
    // IBasicTimer interface
public:
    SoftTimer();
    virtual ~SoftTimer() override;
    virtual void SetTimeout(std::chrono::milliseconds) override;
    virtual void Start() override;
    virtual void StopAndReset() override;
    virtual void SetRepeatMode(repeatMode) override;

private:
    std::atomic<repeatMode> repMode;
    enum class state{idle,running};
    std::atomic<state> myState;
    std::atomic<std::chrono::milliseconds> timeout;
    std::atomic<bool> timerThreadExitRequest;
    std::future<void> timerThreadFuture;
    void timerTask(std::promise<void>&& exitPromise);
    MySignal s;
};
}

#endif

#ifndef IBASICTIMER_H
#define IBASICTIMER_H
#include <chrono>
#include <functional>

/**
 * @brief The BasicTimer Interfacce
 */
class BasicTimer{
protected:
    std::function<void()> timeoutCallback;
public:
    BasicTimer();
    enum class repeatMode{single, continuous};
    virtual ~BasicTimer()=default;
    virtual void SetTimeout(std::chrono::milliseconds)=0;
    void SetTimeoutCallback(std::function<void()>);
    virtual void Start()=0;
    virtual void StopAndReset()=0;
    virtual void SetRepeatMode(repeatMode)=0;
};
#endif

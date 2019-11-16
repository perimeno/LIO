#ifndef INPUTPIN_H
#define INPUTPIN_H
#include <cstdint>
#include <condition_variable>
#include <chrono>
#include <functional>

/**
 * @brief This class represents an input pin.
 */
class InputPin
{
public:
    virtual ~InputPin()=default;
    enum class TriggerEdge{None, Rising, Falling, Both};
    enum class PullUpDown{HiZ, PullUp, PullDown};
    virtual void SetTriggerEdge(TriggerEdge edge)=0;
    virtual void SetPullUpDown(PullUpDown pud)=0;
    /**
     * @brief Starts async event based process
     */
    virtual void StartListening()=0;
    /**
     * @brief Stops async event based process
     */
    virtual void StopListening()=0;

    virtual bool Read()=0;
    virtual uint32_t GetPinNo()=0;
    /**
     * @brief Set the callback that should be called if event occurred
     * @param cb callback where input param represent the input value when the event hapened
     */
    void SetEventCallback(std::function<void(bool)>cb);
    void RemoveEventCallback();
private:
    std::function<void(bool)> eventCb;
    std::mutex eventCbMutex;
    void dummyCb();
protected:
    void callEventCallback();
    InputPin();
};



#endif

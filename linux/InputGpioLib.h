#ifndef INPUTGPIOLIB_H
#define INPUTGPIOLIB_H

#include "InputPthreadBased.h"
#include <cstdint>
#include <future>

/**
 * @brief The Implements InputPin with character device (GPIOLIB) interface
 */
class InputGpioLib:public InputPthreadBased
{
private:

    int chipfd;
    uint32_t pinNo;
    bool isOk();
public:
    /**
     * @brief Construct a gpiolib based wrapper for input pin
     * @param chipName
     * @param pinNo
     */
    InputGpioLib(const char* chipName, uint32_t pinNo);
    virtual ~InputGpioLib()override;
    virtual void SetTriggerEdge(TriggerEdge edge) override;
    virtual bool Read() override;
    virtual uint32_t GetPinNo() override;
    virtual void SetPullUpDown(PullUpDown pud) override;

protected:
    virtual void listenerThreadRunnable(std::promise<void> &&threadExitPromise, int fileDescriptor) override;
};

#endif // INPUTGPIOLIB_H

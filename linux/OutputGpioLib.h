#ifndef OUTPUTGPIOLIB_H
#define OUTPUTGPIOLIB_H
#include "OutputPin.h"
namespace LIO {
/**
 * @brief GPIOLIB based implementation of an output pin
 */
class OutputGpioLib : public OutputPin
{
public:
private:
    int chipfd;
    int linefd;
    uint32_t pinNo;
    bool isLineOk();
public:
    /**
     * @brief Creates an output pin wrapper
     * @param chipName
     * @param pinNo
     */
    OutputGpioLib(const char* chipName, uint32_t pinNo);

    ~OutputGpioLib() override;
    virtual void Write(bool val) override;
    virtual uint32_t GetPinNo() override;
};
}
#endif // OUTPUTGPIOLIB_H

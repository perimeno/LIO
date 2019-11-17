#ifndef OUTPUTSYSFS_H
#define OUTPUTSYSFS_H
#include "OutputPin.h"
#include "SysfsWrapper.h"

namespace LIO {
/**
 * @brief Sysfs based implementation of an output pin
 */
class OutputSysfs:public OutputPin
{

private:
    SysfsWrapper port;

public:
    /**
     * @brief Creates an output pin wrapper.
     * @param pinNo
     */
    OutputSysfs(uint32_t pinNo);

    /**
     * @brief Creates an output pin wrapper. and set ints initial value
     * @param pinNo
     * @param initialValue
     */
    OutputSysfs(uint32_t pinNo,bool initialValue);

    // OutputPort interface
public:
    virtual void Write(bool val) override;
    virtual uint32_t GetPinNo() override;
};
}

#endif // OUTPUTSYSFS_H

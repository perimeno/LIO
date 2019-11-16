#ifndef INPUTSYSFS_H
#define INPUTSYSFS_H
#include <InputPthreadBased.h>
#include <SysfsWrapper.h>
#include <atomic>
#include <future>

/**
 * @brief Sysfs based implementation of InputPin
 */
class InputSysfs : public InputPthreadBased
{
private:
    SysfsWrapper sysfsWrapper;
public:
    InputSysfs(uint32_t pinNo);
    ~InputSysfs() override;
    virtual void SetTriggerEdge(TriggerEdge edge) override;
    virtual void SetPullUpDown(PullUpDown pud) override;
    virtual bool Read() override;
    virtual uint32_t GetPinNo() override;

protected:
    virtual void listenerThreadRunnable(std::promise<void>&& threadExitPromise,int fileDescriptor) override;
};



#endif // INPUTSYSFS_H

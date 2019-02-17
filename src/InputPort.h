#ifndef INPUTPORT_H
#define INPUTPORT_H

#include "GPIO_Linux.h"
#include <mutex>
#include <condition_variable>
/**
 * @brief Represents an input port
 */
class InputPort:public GPIO_Linux
{
private:
    int fd;
public:
    /**
     * @brief Create and config an input port
     * @param GPIO No.
     */
    InputPort(uint32_t pinNo);
    virtual ~InputPort();
    enum class TriggerEdge{None, Rising, Falling, Both};
    void SetTriggerEdge(TriggerEdge edge);
    /**
     * @brief This function blocks the execution maximum for the given time or until event happens on the input pin
     * @param timeout_ms maximum wait time. -1 means wait until event happens
     * @return true if event happened, false otherwise
     */
    bool WaitForValidEvent(int timeout_ms=1000);
    bool Read();
};

#endif // INPUTPORT_H

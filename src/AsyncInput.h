#ifndef ASYNCINPUT_H
#define ASYNCINPUT_H
#include "InputPort.h"
#include "EventHandledInput.h"
#include <thread>
#include <mutex>
#include <condition_variable>
/**
 * @brief Represents an input pin that can inform the outside world from its state change
 */
class AsyncInput: public EventHandledInput
{
private:
    InputPort inputPort;
    std::thread listenigThread;
    std::condition_variable condExit;
    std::mutex mutExit;
    bool exit;
    void Listen();
public:
    AsyncInput(uint32_t portNo);
    void Init();
    void StartListening();
    void StopListening();
};

#endif // ASYNCINPUT_H

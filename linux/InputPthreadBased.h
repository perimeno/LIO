#ifndef INPUTPTHREADBASED_H
#define INPUTPTHREADBASED_H
#include <InputPin.h>
#include <future>

namespace LIO {
/**
 * @brief Helper class for sync input listener. It simplifies thread handling
 */
class InputPthreadBased : public InputPin
{
public:
    virtual void StartListening() override final;
    virtual void StopListening() override final;
protected:
    int fd;
    std::atomic<bool> threadExitRequest;
    InputPthreadBased();
    virtual void listenerThreadRunnable(std::promise<void>&& threadExitPromise,int fileDescriptor)=0;
private:
    std::future<void> exitPerformed;
    enum class listenerThreadState{stopped,started};
    listenerThreadState threadState;
    pthread_t threadNativeId;

};
}

#endif // INPUTPTHREADBASED_H

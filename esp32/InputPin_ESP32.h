#ifndef INPUTPORT_H
#define INPUTPORT_H
#include <InputPin.h>
#include <cstdint>
#include <atomic>
#include <future>
#include <driver/gpio.h>
#include <MySignal.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

namespace LIO{

class InputPin_ESP32:public InputPin{

protected:
    std::atomic<bool> threadExitRequest;
private:
    std::future<void> exitPerformed;
    enum class listenerThreadState{stopped,started};
    listenerThreadState threadState;
    void listenerThreadRunnable(std::promise<void>&& threadExitPromise);
    gpio_num_t gpioNo;
    static void IRAM_ATTR ISR(void*);
    QueueHandle_t eventQueue;
public:
    explicit InputPin_ESP32(gpio_num_t inputPinNo);
    virtual void SetTriggerEdge(TriggerEdge edge) override;
    virtual void SetPullUpDown(PullUpDown pud) override;
    virtual void StartListening() override;
    virtual void StopListening() override;
    virtual bool Read() override;
    virtual uint32_t GetPinNo() override;
};
}
#endif

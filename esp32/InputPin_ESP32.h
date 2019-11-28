#ifndef INPUTPORT_H
#define INPUTPORT_H
#include <InputPin.h>
#include <cstdint>
class InputPin_ESP32:public LIO::InputPin{


    // InputPin interface
public:
    virtual void SetTriggerEdge(TriggerEdge edge) override;
    virtual void SetPullUpDown(PullUpDown pud) override;
    virtual void StartListening() override;
    virtual void StopListening() override;
    virtual bool Read() override;
    virtual uint32_t GetPinNo() override;
};
#endif

#include "OutputPort.h"

OutputPort::OutputPort(uint32_t pinNo):GPIO_Linux (pinNo){
    SetDirection(Direction::Output);
}
OutputPort::OutputPort(uint32_t pinNo,bool DefaultValue):GPIO_Linux(pinNo){
    SetDirection(DefaultValue?Direction::High:Direction::Low);
}

void OutputPort::Write(bool val){
    WriteVal(val);
}

#include "OutputSysfs.h"

OutputSysfs::OutputSysfs(uint32_t pinNo):port(pinNo){
    port.SetDirection(SysfsWrapper::Direction::Output);
}

OutputSysfs::OutputSysfs(uint32_t pinNo, bool initialValue):port(pinNo){
    port.SetDirection(initialValue?SysfsWrapper::Direction::High:SysfsWrapper::Direction::Low);
}
void OutputSysfs::Write(bool val){
    port.WriteVal(val);
}

uint32_t OutputSysfs::GetPinNo(){
    return port.GetPinNo();
}

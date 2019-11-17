#include <sstream>
#include <fcntl.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>

#include "OutputGpioLib.h"

using namespace std;
using namespace LIO;

OutputGpioLib::OutputGpioLib(const char *chipName, uint32_t pinNo){
    stringstream ss;
    ss<<"/dev/"<<chipName;
    chipfd = open(ss.str().c_str(), O_RDWR | O_CLOEXEC);
    if(chipfd>=0){
        gpiohandle_request req{};
        req.flags=GPIOHANDLE_REQUEST_OUTPUT;
        req.lines=1;
        req.lineoffsets[0]=pinNo;
        if(ioctl(chipfd,GPIO_GET_LINEHANDLE_IOCTL,&req)>=0){
            linefd=req.fd;
            if(linefd<0)
                cerr<<"Unable to open line: "<<pinNo<<endl;
        }
        else
            cerr<<"Unable to init line: "<<pinNo<<endl;
    }
    else
        cerr<<"Unable to open chip: "<<ss.str()<<endl;
}

OutputGpioLib::~OutputGpioLib(){
    if(linefd>=0)
        close(linefd);
    if(chipfd>=0)
        close(chipfd);
}

void OutputGpioLib::Write(bool val){
    if(isLineOk()){
        gpiohandle_data data;
        data.values[0]=val;
        if(ioctl(linefd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data)<0)
            cerr<<"Unable write line: "<<pinNo<<endl;
}
}

uint32_t OutputGpioLib::GetPinNo(){
    return pinNo;
}

bool OutputGpioLib::isLineOk(){
    return chipfd>=0 && linefd>=0;
}

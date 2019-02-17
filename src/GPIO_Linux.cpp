#include "GPIO_Linux.h"
#include <sstream>
#include <stdexcept>
#include <syslog.h>
using namespace std;


GPIO_Linux::GPIO_Linux(uint32_t pinNo):_pinNo(pinNo),basePath("/sys/class/gpio"),pinBasePath(""){
    stringstream ss;
    ss<<basePath<<"/gpio"<<_pinNo<<"/";
    pinBasePath=ss.str();

    fstream exp(basePath+"/export");
    if(!exp.good()){
        string err_msg="unable to open IO port - ";
        err_msg.append(to_string(pinNo));
        syslog(LOG_CRIT,"%s",err_msg.c_str());
        throw runtime_error(err_msg);
    }
    exp<<to_string(_pinNo);
}

GPIO_Linux::~GPIO_Linux(){
    fstream unExp(basePath+"/unexport");
    unExp<<to_string(_pinNo);
}

void GPIO_Linux::SetDirection(GPIO_Linux::Direction dir){
    auto direction=make_unique<fstream>(pinBasePath+"direction");
    if(!direction->good()){
        syslog(LOG_CRIT,"Unable to open direction file - %ud",_pinNo);
        throw runtime_error("Unable to open direction");
    }
    switch(dir){
        case Direction::Input:
            *direction<<"in";
            break;
        case Direction::Output:
            *direction<<"out";
            break;
        case Direction::High:
            *direction<<"high";
            break;
        case Direction::Low:
            *direction<<"low";
            break;
    }
}

void GPIO_Linux::SetActiveLow(bool isActiveLow){
    auto activeLow=make_unique<fstream>(pinBasePath+"active_low");
    if(!activeLow->good()){
        syslog(LOG_CRIT,"Unable to open active_low file - %ud",_pinNo);
        throw runtime_error("Unable to open active_low");
    }
    *activeLow<<(isActiveLow?"1":"0");
}

bool GPIO_Linux::ReadVal(){
    auto value=make_unique<fstream>(pinBasePath+"value");
    if(!value->good()){
        syslog(LOG_CRIT,"Unable to open value for read - %ud",_pinNo);
        throw runtime_error("Unable to open value for read");
    }
    bool ret;
    *value>>ret;
    return ret;
}

void GPIO_Linux::WriteVal(bool val){
    auto value=make_unique<fstream>(pinBasePath+"value");
    if(!value->good()){
        syslog(LOG_CRIT,"Unable to open value for write - %ud",_pinNo);
        throw runtime_error("Unable to open value for write");
    }
    *value<<val;
}

uint32_t GPIO_Linux::GetPinNo(){
    return _pinNo;
}

string GPIO_Linux::GetPinBasePath(){
    return pinBasePath;
}

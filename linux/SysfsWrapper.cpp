#include "SysfsWrapper.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;


SysfsWrapper::SysfsWrapper(uint32_t pinNo):_pinNo(pinNo),basePath("/sys/class/gpio"),pinBasePath(""){
    stringstream ss;
    ss<<basePath<<"/gpio"<<_pinNo<<"/";
    pinBasePath=ss.str();

    ofstream exp(basePath+"/export");
    if(!exp.good()){
        cerr<<"unable to open IO port - "<<pinNo<<endl;
        throw runtime_error("output open error");
    }
    exp<<to_string(_pinNo)<<flush;
    exp.close();
    waitForPermission();
}

SysfsWrapper::~SysfsWrapper(){
    ofstream unExp(basePath+"/unexport");
    unExp<<to_string(_pinNo);
}


void SysfsWrapper::SetDirection(SysfsWrapper::Direction dir){
    ofstream direction(pinBasePath+"direction");
    if(!direction.good()){
        throw runtime_error("Unable to open direction");
    }
    switch(dir){
        case Direction::Input:
            direction<<"in";
            break;
        case Direction::Output:
            direction<<"out";
            break;
        case Direction::High:
            direction<<"high";
            break;
        case Direction::Low:
            direction<<"low";
            break;
    }
}

void SysfsWrapper::SetActiveLow(bool isActiveLow){
    ofstream activeLow(pinBasePath+"active_low");
    if(!activeLow.good()){
        cerr<<"Unable to open active_low file - "<<_pinNo<<endl;
        throw runtime_error("Unable to open active_low");
    }
    activeLow<<(isActiveLow?"1":"0");
}

bool SysfsWrapper::ReadVal(){
    ifstream value(pinBasePath+"value");
    if(!value.good()){
        cerr<<"Unable to open value for read - "<<_pinNo;
        throw runtime_error("Unable to open value for read");
    }
    bool ret;
    value>>ret;
    return ret;
}

void SysfsWrapper::WriteVal(bool val){
    ofstream value(pinBasePath+"value");
    if(!value.good()){
        cerr<<"Unable to open value for write - "<<_pinNo<<endl;
        throw runtime_error("Unable to open value for write");
    }
    value<<val;
}

uint32_t SysfsWrapper::GetPinNo(){
    return _pinNo;
}

string SysfsWrapper::GetPinBasePath(){
    return pinBasePath;
}

void SysfsWrapper::waitForPermission(){
    for(int i=0; i<10 && !isPermissionOk(); ++i){//hack to wait until permissions are set correctly on subdescriptors during gdb debug
        cout<<"wait for permission on "<<pinBasePath<<endl;
        this_thread::sleep_for(100ms);
    }
}

bool SysfsWrapper::isPermissionOk(){
    struct stat st;
    bool ret=false;
    if(stat(pinBasePath.c_str(), &st) == 0){
        mode_t perm = st.st_mode;

        ret= (perm&(S_IRGRP|S_IWGRP|S_IXGRP))==(S_IRGRP|S_IWGRP|S_IXGRP);
    }
    else{
        cerr<<"unable to read file permission"<<endl;
    }
    return ret;
}

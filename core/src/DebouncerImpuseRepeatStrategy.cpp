#include "DebouncerImpuseRepeatStrategy.h"
using namespace LIO;
DebouncerImpulseRepeatStrategy::DebouncerImpulseRepeatStrategy():onCb([]{}),offCb([]{}){

}

void DebouncerImpulseRepeatStrategy::setOnCallback(std::function<void()>cb){
    onCb=cb;
}
void DebouncerImpulseRepeatStrategy::setOffCallback(std::function<void()>cb){
    offCb=cb;
}

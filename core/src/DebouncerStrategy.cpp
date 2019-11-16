#include "DebouncerStrategy.h"
DebouncerStrategy::DebouncerStrategy():onCb([]{}),offCb([]{}){

}

void DebouncerStrategy::setOnCallback(std::function<void()>cb){
    onCb=cb;
}
void DebouncerStrategy::setOffCallback(std::function<void()>cb){
    offCb=cb;
}

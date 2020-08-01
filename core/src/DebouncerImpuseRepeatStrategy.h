#ifndef DEBOUNCERIMPULSEREPEATSTRATEGY_H
#define DEBOUNCERIMPULSEREPEATSTRATEGY_H

#include <functional>
namespace LIO {
/**
 * @brief Implementation of this class should determine how @Debouncer should
 * handle the stream of event. i.e. input is 1 continously. These implementation
 * should determine that only one event should be emitted or one event should be
 * emitted in every secondor stg else.
 */
class DebouncerImpulseRepeatStrategy
{
protected:
    std::function<void()>onCb;
    std::function<void()>offCb;
public:
    DebouncerImpulseRepeatStrategy();
    virtual ~DebouncerImpulseRepeatStrategy()=default;
    virtual void handleOnEvent()=0;
    virtual void handleOffEvent()=0;
    void setOnCallback(std::function<void()>);
    void setOffCallback(std::function<void()>);
};
}
#endif // DEBOUNCERIMPULSEREPEATSTRATEGY_H

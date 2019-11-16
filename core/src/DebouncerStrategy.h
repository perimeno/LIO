#ifndef DEBOUNCERSTRATEGY_H
#define DEBOUNCERSTRATEGY_H

#include <functional>

/**
 * @brief Implementation of this class should determine how @Debouncer should
 * handle the stream of event. i.e. input is 1 continously. These implementation
 * should determine that only one event should be emitted or one event should be
 * emitted in every secondor stg else.
 */
class DebouncerStrategy
{
protected:
    std::function<void()>onCb;
    std::function<void()>offCb;
public:
    DebouncerStrategy();
    virtual ~DebouncerStrategy()=default;
    virtual void handleOnEvent()=0;
    virtual void handleOffEvent()=0;
    void setOnCallback(std::function<void()>);
    void setOffCallback(std::function<void()>);
};

#endif // DEBOUNCERSTRATEGY_H

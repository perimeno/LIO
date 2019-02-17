#ifndef EVENTHANDLEDINPUT_H
#define EVENTHANDLEDINPUT_H
#include <functional>
/**
 * @brief Base class of an Input that can inform the outside world from its state change
 */
class EventHandledInput
{
private:
    std::function<void()>onCallback;
    std::function<void()>offCallback;
protected:
    void OnEvent();
    void OffEvent();
    EventHandledInput();
public:
    virtual ~EventHandledInput()=default;
    /**
     * @brief Set a callback that sould be called if input goes 0->1
     */
    virtual void SetOnCallback(std::function<void()>);
    /**
     * @brief Set a callback that sould be called if input goes 1->0
     */
    virtual void SetOffCallback(std::function<void()>);
};

#endif // EVENTHANDLEDINPUT_H

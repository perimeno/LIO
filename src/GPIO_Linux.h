#ifndef GPIO_LINUX_H
#define GPIO_LINUX_H

#include <string>

#include <fstream>
#include <memory>

/**
 * @brief Base class of Input Output pins. Wraps sysfs kernel interface
 */
class GPIO_Linux
{
private:
    uint32_t _pinNo;
    std::string const basePath;
    std::string pinBasePath;

protected:
    enum class Direction{Input, Output, High, Low};
    void SetDirection(Direction dir);
    void SetActiveLow(bool isActiveLow);
    GPIO_Linux(uint32_t pinNo);
    virtual ~GPIO_Linux();
    bool ReadVal();
    void WriteVal(bool val);
    std::string GetPinBasePath();
public:
    uint32_t GetPinNo();

};

#endif // GPIO_LINUX_H

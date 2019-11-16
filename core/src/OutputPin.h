#ifndef IOUTPUTPIN_H
#define IOUTPUTPIN_H
#include <cstdint>
/**
 * @brief Represents an output pin
 */
class OutputPin
{
public:
    virtual~OutputPin()=default;
    virtual void Write(bool val)=0;
    virtual uint32_t GetPinNo()=0;
};

#endif // IOUTPUTPORT_H

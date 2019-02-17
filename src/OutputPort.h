#ifndef OUTPUTPORT_H
#define OUTPUTPORT_H

#include "GPIO_Linux.h"
/**
 * @brief Represents an output port
 */
class OutputPort: public GPIO_Linux
{
public:
    /**
     * @brief Creates and config optput pin. No default value
     * @param pinNo
     */
    OutputPort(uint32_t pinNo);
    /**
     * @brief Creates and config optput pin with the given default value
     * @param pinNo
     * @param DefaultValue
     */
    OutputPort(uint32_t pinNo,bool DefaultValue);
    void Write(bool val);
};

#endif // OUTPUTPORT_H

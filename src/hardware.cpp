// =============================================================================
// Template-Project | Hardware
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "gpioHandler.h"

namespace Hardware
{
    //uint8_t stateReedMidway = 0;
    uint8_t stateReedEnd = 0;

    //EdgeDetection reedMidway(&stateReedMidway);
    EdgeDetection reedEnd(&stateReedEnd);

    void init()
    {

    }

    void updateHardware()
    {
        //stateReedMidway = GPIO::getPort(Port::reedMidway);
        stateReedEnd = GPIO::getPort(Port::reedEnd);
    }
} // namespace Hardware
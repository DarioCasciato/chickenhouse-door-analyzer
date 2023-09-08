// =============================================================================
// Template-Project | Hardware
// =============================================================================

#ifndef _TEMPLATE_PROJECT_HARDWARE_
#define _TEMPLATE_PROJECT_HARDWARE_

#include "configurations.h"
#include "gpio.h"


namespace Hardware
{
    // Port definitions
    enum class Port : uint8_t
    {
        reedMidway      = (uint8_t) GPIO::Port::D5,
        reedEnd         = (uint8_t) GPIO::Port::D6
    };


    extern uint8_t stateReedMidway;
    extern uint8_t stateReedMidway;

    extern EdgeDetection reedMidway;
    extern EdgeDetection reedEnd;


    /// @brief Initializes hardware
    void init();

    /// @brief Fetches hardware values
    void updateHardware();
} // namespace Hardware


#endif // _TEMPLATE_PROJECT_HARDWARE_
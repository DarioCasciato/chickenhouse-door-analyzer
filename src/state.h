// =============================================================================
// Template-Project | State
// =============================================================================

#ifndef _TEMPLATE_PROJECT_STATE_
#define _TEMPLATE_PROJECT_STATE_

#include "hardware.h"

namespace State
{
    enum States : uint8_t
    {
        st_idle,
        st_flashReading
    };

    /// @brief State driver function
    void stateDriver();

    /// @brief Handler for the Idle state
    void stateRecordEvents();

    /// @brief Handler for the Error state
    void stateFlashReading();
} // namespace State

#endif // _TEMPLATE_PROJECT_STATE_
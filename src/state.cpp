// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
#include "configurations.h"
#include "Timer.h"
#include "APIHandlers/apiHandler.h"
#include "Logging.h"

namespace
{
    uint32_t unixTime = 0;
    uint32_t sunriseTime = 0;
    uint32_t sunsetTime = 0;
}

//------------------------------------------------------------------------------

namespace State
{
    States state = States::st_idle;

    void stateDriver()
    {
        switch (State::state)
        {
        case State::st_idle: stateIdle(); break;
        case State::st_error: stateError(); break;

        default:    // catch invalid state (implement safety backup)
        goto exception;
            break;
        }

        return;

        exception:
            for(;;) {}
    }

    // State implementations
    void stateIdle()
    {
        if(Hardware::reedMidway.getEdgePos())
        {
            unixTime = APIHandler::getUnixTime();
            sunriseTime = APIHandler::getSunsetTime();

            log("closing detected! Time: %d\n Sunset time: %d\n", unixTime, sunriseTime);

            // TODO implement sending to Database
        }

        if(Hardware::reedMidway.getEdgeNeg())
        {
            unixTime = APIHandler::getUnixTime();
            sunriseTime = APIHandler::getSunriseTime();

            log("opening detected! Time: %d\n Sunrise time: %d\n", unixTime, sunriseTime);

            // TODO implement sending to Database
        }
    }

    void stateError()
    {

    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions
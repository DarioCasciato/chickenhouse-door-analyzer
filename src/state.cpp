// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
#include "configurations.h"
#include "Timer.h"
#include "APIHandlers/apiHandler.h"
#include "Logging.h"
#include "Flash/Flash.h"

namespace
{
    EventData openEvent;
    EventData closeEvent;
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
            closeEvent.timestamp = APIHandler::getUnixTime();
            closeEvent.SunTime = APIHandler::getSunsetTime();

            log("closing detected! Time: %d\n Sunset time: %d\n", closeEvent.timestamp, closeEvent.SunTime);

            // TODO implement sending to Database or flash
            Flash::closeEvents.write(&closeEvent);
        }

        if(Hardware::reedMidway.getEdgeNeg())
        {
            openEvent.timestamp = APIHandler::getUnixTime();
            openEvent.SunTime = APIHandler::getSunriseTime();

            log("opening detected! Time: %d\n Sunrise time: %d\n", openEvent.timestamp, openEvent.SunTime);

            // TODO implement sending to Database or flash
            Flash::openEvents.write(&openEvent);
        }
    }

    void stateError()
    {

    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions
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

Timer changeState;

namespace
{
    EventData openEvent;
    EventData closeEvent;
}

//------------------------------------------------------------------------------

namespace State
{
    // States state = States::st_idle;
    States state = States::st_flashReading;

    void stateDriver()
    {
        switch (State::state)
        {
        case State::st_idle: stateIdle(); break;
        case State::st_flashReading: stateFlashReading(); break;

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
        if(Hardware::reedEnd.getEdgePos())
        {
            closeEvent.timestamp = APIHandler::getUnixTime();
            closeEvent.SunTime = APIHandler::getSunsetTime();

            log("\nclosing detected! \nTime: %d\nSunset time: %d\n", closeEvent.timestamp, closeEvent.SunTime);

            Flash::closeEvents.write(static_cast<void*>(&closeEvent));
        }

        if(Hardware::reedEnd.getEdgeNeg())
        {
            openEvent.timestamp = APIHandler::getUnixTime();
            openEvent.SunTime = APIHandler::getSunriseTime();


            Flash::openEvents.write(static_cast<void*>(&openEvent));
            log("\nopening detected! \nTime: %d\nSunrise time: %d\n", openEvent.timestamp, openEvent.SunTime);
        }


        if(!changeState.elapsedStart())
            changeState.start();

        if(changeState.elapsed(30000))
        {
            changeState.stop();
            state = States::st_flashReading;
        }
    }

    void stateFlashReading()
    {
        log("\nOpen events:");
        for(uint8_t i = 0; i < Flash::openEvents.getNumEntries(); i++)
        {
            Flash::openEvents.read(i, &openEvent);
            log("Event %d:\tTime: %d   Sunrise time: %d", openEvent.timestamp, openEvent.SunTime);
        }

        log("\n\nClose events:");
        for(uint8_t i = 0; i < Flash::closeEvents.getNumEntries(); i++)
        {
            Flash::closeEvents.read(i, &closeEvent);
            log("Event %d:\tTime: %d   Sunset time: %d", closeEvent.timestamp, closeEvent.SunTime);
        }

        for(;;) { delay(500); }
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions
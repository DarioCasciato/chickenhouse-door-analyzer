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
    States state = States::st_idle;
    //States state = States::st_flashReading;

    void stateDriver()
    {
        switch (State::state)
        {
        case State::st_idle: stateRecordEvents(); break;
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
    void stateRecordEvents()
    {
        // Check if the reed switch detected a positive edge (closing)
        if(Hardware::reedEnd.getEdgePos())
        {
            // Record the current time and sunset time
            closeEvent.timestamp = APIHandler::getUnixTime();
            closeEvent.SunTime = APIHandler::getSunsetTime();

            // Log the event
            log("\nclosing detected! \nTime: %d\nSunset time: %d\n", closeEvent.timestamp, closeEvent.SunTime);

            // Write the close event to flash memory
            Flash::closeEvents.write(static_cast<void*>(&closeEvent));
        }

        // Check if the reed switch detected a negative edge (opening)
        if(Hardware::reedEnd.getEdgeNeg())
        {
            // Record the current time and sunrise time
            openEvent.timestamp = APIHandler::getUnixTime();
            openEvent.SunTime = APIHandler::getSunriseTime();

            // Write the open event to flash memory
            Flash::openEvents.write(static_cast<void*>(&openEvent));

            // Log the event
            log("\nopening detected! \nTime: %d\nSunrise time: %d\n", openEvent.timestamp, openEvent.SunTime);
        }
    }

    // Function to read events from flash memory and log them
    void stateFlashReading()
    {
        // Log open events
        log("\nOpen events:");
        for(uint8_t i = 0; i < Flash::openEvents.getNumEntries(); i++)
        {
            // Read an open event from flash memory
            Flash::openEvents.read(i, &openEvent);

            // Log the event
            log("Event %d:\tTime: %d   Sunrise time: %d", i+1, openEvent.timestamp, openEvent.SunTime);
        }

        // Log close events
        log("\n\nClose events:");
        for(uint8_t i = 0; i < Flash::closeEvents.getNumEntries(); i++)
        {
            // Read a close event from flash memory
            Flash::closeEvents.read(i, &closeEvent);

            // Log the event
            log("Event %d:\tTime: %d   Sunset time: %d", i+1, closeEvent.timestamp, closeEvent.SunTime);
        }

        // Infinite loop to keep the program running
        for(;;) { delay(500); }
    }

} // namespace State

//------------------------------------------------------------------------------

// Other Functions
// =============================================================================
// Utils | FlashStorage
// =============================================================================

#include "Flash.h"
#include "Logging.h"

#define MAGIC_NUMBER 0x4334

namespace Flash
{
    // add flash memory definition here
    // example: FlashStorage testMemory(sizeof(Flash::Structure::memory1), sizeof(DataType), MAGICNUMBER);
    FlashStorage openEvents(sizeof(Flash::Structure::openEvents), sizeof(EventData), MAGIC_NUMBER);
    FlashStorage closeEvents(sizeof(Flash::Structure::closeEvents), sizeof(EventData), MAGIC_NUMBER);

    // Add initializers here
    void initStorage()
    {
        openEvents.init();
        closeEvents.init();
    }


    void init()
    {
        #ifdef ESP8266
        EEPROM.begin(sizeof(Flash::Structure));
        #else
        EEPROM.begin();
        #endif

        initStorage();

        log("Flash memory initialized\n");
    }

    void clear()
    {
        openEvents.clear();
        closeEvents.clear();
    }

} // namespace Flash
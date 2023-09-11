// =============================================================================
// Utils | FlashStorage
// =============================================================================

#include "FlashStorage.h"
#include "FlashStructure.h"
#include <EEPROM.h>

namespace Flash
{
    // add flash memory definition here
    // example: FlashStorage testMemory(sizeof(Flash::Structure::memory1), sizeof(DataType), MAGICNUMBER);
    extern FlashStorage openEvents;
    extern FlashStorage closeEvents;

    void init();

} // namespace Flash

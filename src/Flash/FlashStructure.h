// =============================================================================
// Utils | FlashStorage
// =============================================================================

#ifndef UTILS_FLASH_STRUCTURE_
#define UTILS_FLASH_STRUCTURE_

#include <stdint.h>

namespace Flash
{
    struct Structure
    {
        uint8_t openEvents[0x200]; // 512 bytes
        uint8_t closeEvents[0x200]; // 512 bytes
    };
} // namespace Flash

struct EventData
{
    uint32_t timestamp;
    uint32_t SunTime;
};


#endif // UTILS_FLASH_STRUCTURE_
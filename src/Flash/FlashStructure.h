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

enum class WeatherMain : uint8_t
{
    Clear,
    Clouds,
    Rain,
    Drizzle,
    Thunderstorm,
    Snow,
    Mist,
    Smoke,
    Haze,
    Dust,
    Fog,
    Sand,
    Ash,
    Squall,
    Tornado,
    Unknown = 0xFF // For any other conditions not listed
};

struct EventData
{
    uint32_t timestamp;
    uint32_t SunTime;
    WeatherMain weatherCondition;
};


#endif // UTILS_FLASH_STRUCTURE_
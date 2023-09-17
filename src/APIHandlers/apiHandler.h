// =============================================================================
// Template-Project | API Handler
// =============================================================================

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Flash/FlashStructure.h"

namespace APIHandler
{
    /// @brief Sends a GET request to the API.
    ///
    /// @return The current unix time.
    uint32_t getUnixTime();

    /// @brief Sends a GET request to the API.
    ///
    /// @return The todays sunrise time.
    uint32_t getSunsetTime();

    /// @brief Sends a GET request to the API.
    ///
    /// @return The todays sunset time.
    uint32_t getSunriseTime();

    /// @brief Sends a GET request to the API.
    ///
    /// @return The current weather condition.
    WeatherMain getWeatherCondition();

    /// @brief Converts the weather condition enum to a string.
    ///
    /// @param weatherCondition The weather condition enum.
    const char* enumToString(WeatherMain weatherCondition);

    namespace Notification
    {
        /// @brief Sends a GET request to the API for door open notification.
        void doorOpen();

        /// @brief Sends a GET request to the API for door close notification.
        void doorClose();
    } // namespace Notification

}
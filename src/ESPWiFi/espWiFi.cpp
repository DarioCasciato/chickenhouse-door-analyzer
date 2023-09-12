// =============================================================================
// Template-Project | Main
// =============================================================================

#include "espWiFi.h"
#include "configurations.h"

namespace
{
    inline const char* ssid = "Wi-Fi 2";
    inline const char* password = "rc7145!!";
}


void Wifi::establish()
{
    WiFi.hostname("Chickendoor Monitor");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi!");
}

// =============================================================================
// Template-Project | Main
// =============================================================================

#include "espWiFi.h"
#include "configurations.h"

namespace
{
    inline const char* ssid = "SSID_HERE";
    inline const char* password = "PASSWORD_HERE";
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

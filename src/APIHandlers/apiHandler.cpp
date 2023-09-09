// =============================================================================
// Template-Project | Main
// =============================================================================

#include "apiHandler.h"
#include "configurations.h"

// returs the current unix time. uses api_datetime from configurations.h
// parses the response from the API and returns the unix time
uint32_t APIHandler::getUnixTime()
{
    WiFiClient client;
    HTTPClient http;

    http.begin(client, api_datetime);
    int httpCode = http.GET();

    if (httpCode > 0)
    {
        String payload = http.getString();
        int index = payload.indexOf("unixtime");

        if (index != -1)
        {
          String unixTime = payload.substring(index + 11, index + 21);
          http.end();
          return unixTime.toInt();
        }
        else
        {
          Serial.println("unixtime not found in API response");
          http.end();
          return 0;
        }
    }
    else
    {
        Serial.println("Error on HTTP request");
        http.end();
        return 0;
    }
}

uint32_t APIHandler::getSunsetTime()
{
    uint32_t sunsetTime = 0;
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(String(api_suntime) + String(api_key));
        int httpCode = http.GET();

        if (httpCode > 0)
        {
            String payload = http.getString();
            int index = payload.indexOf("\"sunset\":");
            if (index != -1)
            {
                String sunset = payload.substring(index + 9, index + 19);
                sunsetTime = sunset.toInt();
            }
        }

        http.end();
    }
    return sunsetTime;
}

uint32_t APIHandler::getSunriseTime()
{
    uint32_t sunriseTime = 0;
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(String(api_suntime) + String(api_key));
        int httpCode = http.GET();

        if (httpCode > 0)
        {
            String payload = http.getString();
            int index = payload.indexOf("\"sunrise\":");
            if (index != -1)
            {
                String sunrise = payload.substring(index + 10, index + 20);
                sunriseTime = sunrise.toInt();
            }
        }

        http.end();
    }
    return sunriseTime;
}

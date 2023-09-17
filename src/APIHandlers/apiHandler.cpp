// =============================================================================
// Template-Project | Main
// =============================================================================

#include "apiHandler.h"
#include "configurations.h"
#include "apiKey.h"
#include <ArduinoJson.h>

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
        http.end();  // Close the connection as soon as you get the payload

        DynamicJsonDocument doc(1024);  // Create a DynamicJsonDocument with a suitable capacity
        DeserializationError error = deserializeJson(doc, payload);  // Parse the JSON payload

        if (error)  // Check for parsing errors
        {
            Serial.println("Failed to parse JSON");
            return 0;
        }

        uint32_t unixTime = doc["unixtime"];  // Extract the Unix time
        return unixTime;
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
        WiFiClient client;
        HTTPClient http;
        http.begin(client, String(api_openweather) + String(api_key_owm));
        int httpCode = http.GET();

        if (httpCode > 0)
        {
            String payload = http.getString();
            http.end();  // Close the connection

            DynamicJsonDocument doc(2048);  // Create a DynamicJsonDocument
            DeserializationError error = deserializeJson(doc, payload);

            if (error)
            {
                Serial.println("Failed to parse JSON");
                return 0;
            }

            sunsetTime = doc["sys"]["sunset"];  // Extract sunset time
        }
    }
    return sunsetTime;
}


uint32_t APIHandler::getSunriseTime()
{
    uint32_t sunriseTime = 0;
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, String(api_openweather) + String(api_key_owm));
        int httpCode = http.GET();

        if (httpCode > 0)
        {
            String payload = http.getString();
            http.end();  // Close the connection

            DynamicJsonDocument doc(2048);  // Create a DynamicJsonDocument
            DeserializationError error = deserializeJson(doc, payload);

            if (error)
            {
                Serial.println("Failed to parse JSON");
                return 0;
            }

            sunriseTime = doc["sys"]["sunrise"];  // Extract sunrise time
        }
    }
    return sunriseTime;
}

WeatherMain APIHandler::getWeatherCondition()
{
    WeatherMain weatherCondition = WeatherMain::Unknown;
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, String(api_openweather) + String(api_key_owm));
        int httpCode = http.GET();

        if (httpCode > 0)
        {
            String payload = http.getString();
            http.end();  // Close the connection

            DynamicJsonDocument doc(2048);  // Create a DynamicJsonDocument
            DeserializationError error = deserializeJson(doc, payload);

            if (error)
            {
                Serial.println("Failed to parse JSON");
                return WeatherMain::Unknown;
            }

            String weather = doc["weather"][0]["main"];  // Extract weather condition

            if (weather == "Clear")                 weatherCondition = WeatherMain::Clear;
            else if (weather == "Clouds")           weatherCondition = WeatherMain::Clouds;
            else if (weather == "Rain")             weatherCondition = WeatherMain::Rain;
            else if (weather == "Drizzle")          weatherCondition = WeatherMain::Drizzle;
            else if (weather == "Thunderstorm")     weatherCondition = WeatherMain::Thunderstorm;
            else if (weather == "Snow")             weatherCondition = WeatherMain::Snow;
            else if (weather == "Mist")             weatherCondition = WeatherMain::Mist;
            else if (weather == "Smoke")            weatherCondition = WeatherMain::Smoke;
            else if (weather == "Haze")             weatherCondition = WeatherMain::Haze;
            else if (weather == "Dust")             weatherCondition = WeatherMain::Dust;
            else if (weather == "Fog")              weatherCondition = WeatherMain::Fog;
            else if (weather == "Sand")             weatherCondition = WeatherMain::Sand;
            else if (weather == "Ash")              weatherCondition = WeatherMain::Ash;
            else if (weather == "Squall")           weatherCondition = WeatherMain::Squall;
            else if (weather == "Tornado")          weatherCondition = WeatherMain::Tornado;
            else                                    weatherCondition = WeatherMain::Unknown;
        }
    }
    return weatherCondition;
}


void APIHandler::Notification::doorOpen()
{
    if(WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, String(request_open) + String(api_key_ifttt));
        int httpResponseCode = http.POST("");

            // Check the response code
        if (httpResponseCode == HTTP_CODE_OK) {
            Serial.print("Notification sent: ");
            Serial.println("DOOR_OPEN_EVENT");
        }

        else
        {
            Serial.print("Error sending notification. Response code: ");
            Serial.println(httpResponseCode);
        }

        // Close the connection
        http.end();
    }
}

void APIHandler::Notification::doorClose()
{
    if(WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, String(request_close) + String(api_key_ifttt));
        int httpResponseCode = http.POST("");

            // Check the response code
        if (httpResponseCode == HTTP_CODE_OK) {
            Serial.print("Notification sent: ");
            Serial.println("DOOR_CLOSE_EVENT");
        }

        else
        {
            Serial.print("Error sending notification. Response code: ");
            Serial.println(httpResponseCode);
        }

        // Close the connection
        http.end();
    }
}

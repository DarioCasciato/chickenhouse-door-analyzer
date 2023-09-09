// =============================================================================
// Template-Project | Main
// =============================================================================

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "hardware.h"
#include "EdgeDetection.h"
#include "configurations.h"
#include "state.h"
#include "ESPWiFi/espWiFi.h"

void refreshData();

//------------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  ESP.wdtEnable(WDTO_1S);

  Wifi::establish();
}

void loop()
{
  for (;;)
  {
    refreshData();

    State::stateDriver();

    ESP.wdtFeed();
  }
}

//------------------------------------------------------------------------------

void refreshData()
{

  Hardware::updateHardware();
  EdgeDetection::updateEdges();
}
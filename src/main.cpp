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
#include "Flash/Flash.h"
#include "ESPWiFi/espWiFi.h"

void refreshData();

//------------------------------------------------------------------------------

void setup()
{
  ESP.wdtEnable(WDTO_1S);
  Serial.begin(115200);

  Flash::init();

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
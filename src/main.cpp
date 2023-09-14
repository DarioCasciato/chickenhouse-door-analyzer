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
#include <EEPROM.h>
#include "Logging.h"

void refreshData();

//------------------------------------------------------------------------------

void setup()
{
  ESP.wdtEnable(WDTO_1S);
  Serial.begin(115200);

  EEPROM.begin(sizeof(Flash::Structure));
  // read first 14 bytes of the eeprom and print with log
    for (int i = 0; i < 14; i++)
    {
        log("EEPROM %d: %d\n", i, EEPROM.read(i));
    }

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
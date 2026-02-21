#pragma once

#include <ArduinoOTA.h>
#include <ESPAsyncWebServer.h>
#include "config.h"

class OTAManager {
public:
    void begin(const String& hostname = "medidor-trifasico");
    void loop();
    void setupWebOTA(AsyncWebServer* server);

private:
    static const char* _updatePage;
};

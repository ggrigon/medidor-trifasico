#pragma once

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "config.h"
#include "ota_manager.h"

class WebServerManager {
public:
    void begin();
    void broadcast(const MeterData& data);
    void sendAlarm(const String& message);
    AsyncWebServer* getServer() { return _server; }

private:
    AsyncWebServer* _server = nullptr;
    AsyncWebSocket* _ws = nullptr;

    String buildJSON(const MeterData& data);
    void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client,
                   AwsEventType type, void* arg, uint8_t* data, size_t len);
};

#pragma once

#include <PubSubClient.h>
#include <WiFiClient.h>
#include "config.h"

class MQTTClient {
public:
    void begin();
    void loop();
    void publish(const MeterData& data);
    void publishAlarm(int phase, const String& type, float voltage);
    bool isConnected() const;

private:
    WiFiClient _wifiClient;
    PubSubClient* _client = nullptr;
    unsigned long _lastReconnectAttempt = 0;

    void reconnect();
    void publishPhase(int index, const PhaseData& phase);
};

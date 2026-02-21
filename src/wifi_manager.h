#pragma once

#include <WiFi.h>
#include "config.h"

class WiFiManager {
public:
    void begin();
    void check();
    String getIP() const;
    bool isConnected() const;
    bool isAP() const;

private:
    bool _apMode = false;
    void startAP();
};

#pragma once

#include <Adafruit_SSD1306.h>
#include "config.h"

class DisplayManager {
public:
    void begin();
    void update(const MeterData& data, const String& ip, bool hasAlarm);
    void showMessage(const String& line1, const String& line2 = "");

private:
    Adafruit_SSD1306* _display = nullptr;
    uint8_t _currentPage = 0;
    unsigned long _lastPageChange = 0;

    void drawOverview(const MeterData& data);
    void drawPhaseDetail(const MeterData& data, int phase);
    void drawAlarmPage(const MeterData& data);
    void drawStatusBar(const String& ip, bool hasAlarm);
};

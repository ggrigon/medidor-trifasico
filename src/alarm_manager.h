#pragma once

#include <Arduino.h>
#include "config.h"

struct AlarmState {
    int overCount  = 0;
    int underCount = 0;
    int normalCount = 0;
    bool overActive  = false;
    bool underActive = false;
};

class AlarmManager {
public:
    void begin();
    void check(const MeterData& data);
    bool hasActiveAlarm() const;
    String getAlarmMessage() const;

    // Callbacks para integracao com web_server e mqtt
    using AlarmCallback = void(*)(int phase, const String& type, float voltage);
    void onAlarm(AlarmCallback cb) { _callback = cb; }

private:
    AlarmState _state[3];
    bool _buzzerOn = false;
    unsigned long _lastBuzz = 0;
    AlarmCallback _callback = nullptr;

    void activateBuzzer();
    void deactivateBuzzer();
};

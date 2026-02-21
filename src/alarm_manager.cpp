#include "alarm_manager.h"

void AlarmManager::begin() {
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    Serial.println("[ALARM] Inicializado");
}

void AlarmManager::check(const MeterData& data) {
    bool anyAlarm = false;

    for (int i = 0; i < 3; i++) {
        if (!data.phase[i].valid) continue;

        float v = data.phase[i].voltage;
        AlarmState& s = _state[i];

        if (v > ALARM_OVERVOLTAGE) {
            s.overCount++;
            s.normalCount = 0;
            s.underCount = 0;

            if (s.overCount >= ALARM_DEBOUNCE_ON && !s.overActive) {
                s.overActive = true;
                Serial.printf("[ALARM] SOBRETENSAO L%d: %.1fV\n", i + 1, v);
                if (_callback) _callback(i, "overvoltage", v);
            }
        } else if (v < ALARM_UNDERVOLTAGE) {
            s.underCount++;
            s.normalCount = 0;
            s.overCount = 0;

            if (s.underCount >= ALARM_DEBOUNCE_ON && !s.underActive) {
                s.underActive = true;
                Serial.printf("[ALARM] SUBTENSAO L%d: %.1fV\n", i + 1, v);
                if (_callback) _callback(i, "undervoltage", v);
            }
        } else {
            s.normalCount++;
            s.overCount = 0;
            s.underCount = 0;

            if (s.normalCount >= ALARM_DEBOUNCE_OFF) {
                if (s.overActive || s.underActive) {
                    Serial.printf("[ALARM] Clear L%d: %.1fV\n", i + 1, v);
                    if (_callback) _callback(i, "clear", v);
                }
                s.overActive = false;
                s.underActive = false;
            }
        }

        if (s.overActive || s.underActive) {
            anyAlarm = true;
        }
    }

    if (anyAlarm) {
        activateBuzzer();
        digitalWrite(LED_PIN, HIGH);
    } else {
        deactivateBuzzer();
        digitalWrite(LED_PIN, LOW);
    }
}

bool AlarmManager::hasActiveAlarm() const {
    for (int i = 0; i < 3; i++) {
        if (_state[i].overActive || _state[i].underActive) return true;
    }
    return false;
}

String AlarmManager::getAlarmMessage() const {
    String msg;
    for (int i = 0; i < 3; i++) {
        if (_state[i].overActive) {
            if (msg.length() > 0) msg += " | ";
            msg += "L" + String(i + 1) + ":SOBRE";
        }
        if (_state[i].underActive) {
            if (msg.length() > 0) msg += " | ";
            msg += "L" + String(i + 1) + ":SUB";
        }
    }
    return msg;
}

void AlarmManager::activateBuzzer() {
    unsigned long now = millis();
    // Buzzer intermitente: 200ms on, 800ms off
    if (now - _lastBuzz >= 1000) {
        _lastBuzz = now;
        tone(BUZZER_PIN, 2000, 200);
    }
}

void AlarmManager::deactivateBuzzer() {
    noTone(BUZZER_PIN);
}

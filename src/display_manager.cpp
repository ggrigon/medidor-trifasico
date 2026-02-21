#include "display_manager.h"
#include <Wire.h>

void DisplayManager::begin() {
    Wire.begin(OLED_SDA, OLED_SCL);
    _display = new Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

    if (!_display->begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("[OLED] Falha na inicializacao!");
        return;
    }

    _display->clearDisplay();
    _display->setTextSize(1);
    _display->setTextColor(SSD1306_WHITE);
    _display->setCursor(0, 20);
    _display->println("Medidor Trifasico");
    _display->println("Inicializando...");
    _display->display();
    Serial.println("[OLED] Inicializado");
}

void DisplayManager::showMessage(const String& line1, const String& line2) {
    if (!_display) return;
    _display->clearDisplay();
    _display->setTextSize(1);
    _display->setCursor(0, 20);
    _display->println(line1);
    if (line2.length() > 0) {
        _display->println(line2);
    }
    _display->display();
}

void DisplayManager::update(const MeterData& data, const String& ip, bool hasAlarm) {
    if (!_display) return;

    unsigned long now = millis();
    if (now - _lastPageChange >= DISPLAY_PAGE_INTERVAL) {
        _lastPageChange = now;
        _currentPage = (_currentPage + 1) % DISPLAY_NUM_PAGES;
    }

    _display->clearDisplay();
    drawStatusBar(ip, hasAlarm);

    switch (_currentPage) {
        case 0: drawOverview(data);          break;
        case 1: drawPhaseDetail(data, 0);    break;
        case 2: drawPhaseDetail(data, 1);    break;
        case 3: drawPhaseDetail(data, 2);    break;
        case 4: drawAlarmPage(data);         break;
    }

    _display->display();
}

void DisplayManager::drawStatusBar(const String& ip, bool hasAlarm) {
    _display->setTextSize(1);
    _display->setCursor(0, 0);
    _display->print(ip);
    if (hasAlarm) {
        _display->setCursor(104, 0);
        _display->print("ALRM");
    }
    _display->drawLine(0, 9, 127, 9, SSD1306_WHITE);
}

void DisplayManager::drawOverview(const MeterData& data) {
    _display->setTextSize(1);
    float totalP = 0;
    const char* labels[] = {"L1", "L2", "L3"};

    for (int i = 0; i < 3; i++) {
        int y = 12 + i * 14;
        _display->setCursor(0, y);
        _display->print(labels[i]);
        _display->print(":");

        if (data.phase[i].valid) {
            _display->setCursor(18, y);
            _display->printf("%5.1fV", data.phase[i].voltage);
            _display->setCursor(66, y);
            _display->printf("%5.1fA", data.phase[i].current);

            _display->setCursor(18, y + 7);
            _display->printf("%6.0fW  PF:%.2f", data.phase[i].power, data.phase[i].powerFactor);

            totalP += data.phase[i].power;
        } else {
            _display->setCursor(18, y);
            _display->print("-- sem leitura --");
        }
    }

    _display->setCursor(0, 56);
    _display->printf("Total: %.0fW", totalP);
}

void DisplayManager::drawPhaseDetail(const MeterData& data, int phase) {
    _display->setTextSize(1);
    int y = 12;

    _display->setCursor(0, y);
    _display->printf("=== Fase L%d ===", phase + 1);
    y += 10;

    if (!data.phase[phase].valid) {
        _display->setCursor(0, y + 10);
        _display->print("Sem leitura");
        return;
    }

    const PhaseData& p = data.phase[phase];

    _display->setCursor(0, y);
    _display->printf("Tensao:  %6.1f V", p.voltage);
    y += 9;
    _display->setCursor(0, y);
    _display->printf("Corrente:%6.2f A", p.current);
    y += 9;
    _display->setCursor(0, y);
    _display->printf("Potencia:%6.0f W", p.power);
    y += 9;
    _display->setCursor(0, y);
    _display->printf("Energia: %6.2f kWh", p.energy);
    y += 9;
    _display->setCursor(0, y);
    _display->printf("Freq:%5.1fHz PF:%.2f", p.frequency, p.powerFactor);
}

void DisplayManager::drawAlarmPage(const MeterData& data) {
    _display->setTextSize(1);
    _display->setCursor(0, 12);
    _display->println("=== Alarmes ===");

    int y = 24;
    for (int i = 0; i < 3; i++) {
        _display->setCursor(0, y);
        if (!data.phase[i].valid) {
            _display->printf("L%d: sem dados", i + 1);
        } else if (data.phase[i].voltage > ALARM_OVERVOLTAGE) {
            _display->printf("L%d: SOBRE %.1fV!", i + 1, data.phase[i].voltage);
        } else if (data.phase[i].voltage < ALARM_UNDERVOLTAGE) {
            _display->printf("L%d: SUB   %.1fV!", i + 1, data.phase[i].voltage);
        } else {
            _display->printf("L%d: OK    %.1fV", i + 1, data.phase[i].voltage);
        }
        y += 12;
    }
}

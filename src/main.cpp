#include <Arduino.h>
#include "config.h"
#include "wifi_manager.h"
#include "ntp_time.h"
#include "pzem_reader.h"
#include "display_manager.h"
#include "web_server.h"
#include "sd_logger.h"
#include "mqtt_client.h"
#include "alarm_manager.h"
#include "ota_manager.h"

// --- Instancias dos modulos ---
WiFiManager   wifiMgr;
NTPTime       ntpTime;
PZEMReader    pzemReader;
DisplayManager displayMgr;
WebServerManager webServer;
SDLogger      sdLogger;
MQTTClient    mqttClient;
AlarmManager  alarmMgr;
OTAManager    otaMgr;

// --- Dados compartilhados ---
MeterData meterData;

// --- Timers (millis) ---
unsigned long lastPZEM      = 0;
unsigned long lastDisplay   = 0;
unsigned long lastWebSocket = 0;
unsigned long lastSDLog     = 0;
unsigned long lastMQTT      = 0;
unsigned long lastAlarm     = 0;
unsigned long lastWiFiCheck = 0;
unsigned long lastNTPSync   = 0;

// --- Callback de alarme ---
void onAlarm(int phase, const String& type, float voltage) {
    String msg = "L" + String(phase + 1) + " " + type + " " + String(voltage, 1) + "V";
    webServer.sendAlarm(msg);
    mqttClient.publishAlarm(phase, type, voltage);
}

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("\n============================");
    Serial.println(" Medidor Trifasico ESP32");
    Serial.println("============================\n");

    // 1. Display (mostra mensagens de status durante init)
    displayMgr.begin();
    displayMgr.showMessage("Conectando WiFi...");

    // 2. WiFi
    wifiMgr.begin();
    displayMgr.showMessage("WiFi: " + wifiMgr.getIP());

    // 3. NTP
    ntpTime.begin();
    ntpTime.sync();

    // 4. PZEM
    displayMgr.showMessage("Init PZEMs...");
    pzemReader.begin();

    // 5. Web Server + OTA
    webServer.begin();
    otaMgr.begin();
    otaMgr.setupWebOTA(webServer.getServer());

    // 6. SD Card
    displayMgr.showMessage("Init SD Card...");
    sdLogger.begin();

    // 7. MQTT
    mqttClient.begin();

    // 8. Alarmes
    alarmMgr.begin();
    alarmMgr.onAlarm(onAlarm);

    Serial.println("\n[MAIN] Todos os modulos inicializados!");
    Serial.printf("[MAIN] IP: %s\n", wifiMgr.getIP().c_str());
    Serial.printf("[MAIN] SD: %s\n", sdLogger.isReady() ? "OK" : "FALHA");
    Serial.println("[MAIN] Loop cooperativo iniciado\n");
}

void loop() {
    unsigned long now = millis();

    // Leitura PZEMs (1s)
    if (now - lastPZEM >= INTERVAL_PZEM) {
        lastPZEM = now;
        pzemReader.readAll(meterData);
        meterData.isoTime = ntpTime.getISO8601();
    }

    // Update OLED (500ms)
    if (now - lastDisplay >= INTERVAL_DISPLAY) {
        lastDisplay = now;
        displayMgr.update(meterData, wifiMgr.getIP(), alarmMgr.hasActiveAlarm());
    }

    // WebSocket broadcast (1s)
    if (now - lastWebSocket >= INTERVAL_WEBSOCKET) {
        lastWebSocket = now;
        webServer.broadcast(meterData);
    }

    // Log SD Card (10s)
    if (now - lastSDLog >= INTERVAL_SD_LOG) {
        lastSDLog = now;
        sdLogger.log(meterData);
    }

    // Publish MQTT (5s)
    if (now - lastMQTT >= INTERVAL_MQTT) {
        lastMQTT = now;
        mqttClient.publish(meterData);
    }

    // Check alarmes (1s)
    if (now - lastAlarm >= INTERVAL_ALARM) {
        lastAlarm = now;
        alarmMgr.check(meterData);
    }

    // Check WiFi (30s)
    if (now - lastWiFiCheck >= INTERVAL_WIFI) {
        lastWiFiCheck = now;
        wifiMgr.check();
    }

    // Sync NTP (1h)
    if (now - lastNTPSync >= INTERVAL_NTP) {
        lastNTPSync = now;
        ntpTime.sync();
    }

    // MQTT loop (non-blocking)
    mqttClient.loop();

    // OTA loop (ArduinoOTA)
    otaMgr.loop();
}

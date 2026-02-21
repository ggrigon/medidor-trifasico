#pragma once

#include <Arduino.h>

// --- Pinos PZEM (Serial2) ---
#define PZEM_RX_PIN    16
#define PZEM_TX_PIN    17

// --- Pinos OLED (I2C) ---
#define OLED_SDA       21
#define OLED_SCL       22
#define OLED_WIDTH     128
#define OLED_HEIGHT    64
#define OLED_ADDR      0x3C

// --- Pinos SD Card (SPI) ---
#define SD_CS_PIN       5
#define SD_MOSI_PIN    23
#define SD_MISO_PIN    19
#define SD_SCK_PIN     18

// --- Buzzer e LED ---
#define BUZZER_PIN      4
#define LED_PIN         2

// --- Enderecos Modbus PZEM ---
#define PZEM_ADDR_L1   0x01
#define PZEM_ADDR_L2   0x02
#define PZEM_ADDR_L3   0x03

// --- WiFi ---
#define WIFI_SSID       "SEU_SSID"
#define WIFI_PASSWORD   "SUA_SENHA"
#define AP_SSID         "Medidor-Config"
#define AP_PASSWORD     "12345678"
#define WIFI_TIMEOUT_MS 15000

// --- MQTT ---
#define MQTT_SERVER     "192.168.1.100"
#define MQTT_PORT       1883
#define MQTT_USER       ""
#define MQTT_PASSWORD   ""
#define MQTT_CLIENT_ID  "medidor-trifasico"
#define MQTT_TOPIC_BASE "medidor"

// --- NTP ---
#define NTP_SERVER      "pool.ntp.org"
#define NTP_GMT_OFFSET  -10800  // BRT = UTC-3
#define NTP_DST_OFFSET  0

// --- Intervalos (ms) ---
#define INTERVAL_PZEM       1000
#define INTERVAL_DISPLAY     500
#define INTERVAL_WEBSOCKET  1000
#define INTERVAL_SD_LOG    10000
#define INTERVAL_MQTT       5000
#define INTERVAL_ALARM      1000
#define INTERVAL_WIFI      30000
#define INTERVAL_NTP     3600000

// --- Display ---
#define DISPLAY_PAGE_INTERVAL 5000
#define DISPLAY_NUM_PAGES     5

// --- Alarmes ---
#define ALARM_OVERVOLTAGE   253.0f  // +15% de 220V
#define ALARM_UNDERVOLTAGE  197.0f  // -10% de 220V
#define ALARM_DEBOUNCE_ON       3   // leituras consecutivas para ativar
#define ALARM_DEBOUNCE_OFF      5   // leituras consecutivas para desativar

// --- SD Logger ---
#define SD_LOG_DIR      "/logs"

// --- Estruturas de dados ---
struct PhaseData {
    float voltage    = 0;
    float current    = 0;
    float power      = 0;
    float energy     = 0;
    float frequency  = 0;
    float powerFactor = 0;
    bool valid       = false;
};

struct MeterData {
    PhaseData phase[3];
    unsigned long timestamp = 0;
    String isoTime;
};

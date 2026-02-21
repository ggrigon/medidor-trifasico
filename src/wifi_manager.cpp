#include "wifi_manager.h"

void WiFiManager::begin() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.printf("[WiFi] Conectando a %s", WIFI_SSID);
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < WIFI_TIMEOUT_MS) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        _apMode = false;
        Serial.printf("[WiFi] Conectado! IP: %s\n", WiFi.localIP().toString().c_str());
    } else {
        Serial.println("[WiFi] Falha na conexao STA, iniciando AP...");
        startAP();
    }
}

void WiFiManager::startAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    _apMode = true;
    Serial.printf("[WiFi] AP ativo: %s - IP: %s\n", AP_SSID, WiFi.softAPIP().toString().c_str());
}

void WiFiManager::check() {
    if (_apMode) return;

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[WiFi] Desconectado, reconectando...");
        WiFi.reconnect();
    }
}

String WiFiManager::getIP() const {
    if (_apMode) {
        return WiFi.softAPIP().toString();
    }
    return WiFi.localIP().toString();
}

bool WiFiManager::isConnected() const {
    return WiFi.status() == WL_CONNECTED || _apMode;
}

bool WiFiManager::isAP() const {
    return _apMode;
}

#include "web_server.h"
#include <LittleFS.h>

void WebServerManager::begin() {
    if (!LittleFS.begin(true)) {
        Serial.println("[WEB] Falha ao montar LittleFS!");
    }

    _server = new AsyncWebServer(80);
    _ws = new AsyncWebSocket("/ws");

    _ws->onEvent([this](AsyncWebSocket* server, AsyncWebSocketClient* client,
                        AwsEventType type, void* arg, uint8_t* data, size_t len) {
        this->onWsEvent(server, client, type, arg, data, len);
    });
    _server->addHandler(_ws);

    // Servir arquivos do LittleFS
    _server->serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

    // API endpoint para dados atuais (fallback sem WebSocket)
    _server->on("/api/data", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(200, "text/plain", "Use WebSocket /ws");
    });

    _server->begin();
    Serial.println("[WEB] Servidor iniciado na porta 80");
}

void WebServerManager::broadcast(const MeterData& data) {
    if (!_ws || _ws->count() == 0) return;

    String json = buildJSON(data);
    _ws->textAll(json);
}

void WebServerManager::sendAlarm(const String& message) {
    if (!_ws || _ws->count() == 0) return;

    JsonDocument doc;
    doc["type"] = "alarm";
    doc["msg"] = message;

    char buffer[256];
    serializeJson(doc, buffer);
    _ws->textAll(buffer);
}

String WebServerManager::buildJSON(const MeterData& data) {
    JsonDocument doc;
    doc["type"] = "data";
    doc["ts"] = data.isoTime;

    float totalP = 0;
    JsonArray phases = doc["phases"].to<JsonArray>();
    const char* names[] = {"L1", "L2", "L3"};

    for (int i = 0; i < 3; i++) {
        JsonObject p = phases.add<JsonObject>();
        p["id"] = names[i];
        p["ok"] = data.phase[i].valid;

        if (data.phase[i].valid) {
            p["v"]  = round(data.phase[i].voltage * 10) / 10.0;
            p["i"]  = round(data.phase[i].current * 100) / 100.0;
            p["p"]  = round(data.phase[i].power * 10) / 10.0;
            p["e"]  = round(data.phase[i].energy * 1000) / 1000.0;
            p["f"]  = round(data.phase[i].frequency * 10) / 10.0;
            p["pf"] = round(data.phase[i].powerFactor * 100) / 100.0;
            totalP += data.phase[i].power;
        }
    }
    doc["total_p"] = round(totalP * 10) / 10.0;

    char buffer[512];
    serializeJson(doc, buffer);
    return String(buffer);
}

void WebServerManager::onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client,
                                  AwsEventType type, void* arg, uint8_t* data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("[WS] Cliente #%u conectado de %s\n",
                          client->id(), client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("[WS] Cliente #%u desconectado\n", client->id());
            break;
        case WS_EVT_ERROR:
            Serial.printf("[WS] Erro no cliente #%u\n", client->id());
            break;
        default:
            break;
    }
}

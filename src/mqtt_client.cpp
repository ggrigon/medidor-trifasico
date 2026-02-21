#include "mqtt_client.h"
#include <ArduinoJson.h>

void MQTTClient::begin() {
    _client = new PubSubClient(_wifiClient);
    _client->setServer(MQTT_SERVER, MQTT_PORT);
    _client->setBufferSize(512);

    Serial.printf("[MQTT] Configurado - servidor: %s:%d\n", MQTT_SERVER, MQTT_PORT);
}

void MQTTClient::loop() {
    if (!_client) return;

    if (!_client->connected()) {
        unsigned long now = millis();
        if (now - _lastReconnectAttempt > 5000) {
            _lastReconnectAttempt = now;
            reconnect();
        }
    } else {
        _client->loop();
    }
}

void MQTTClient::reconnect() {
    String lwt = String(MQTT_TOPIC_BASE) + "/status";

    bool connected;
    if (strlen(MQTT_USER) > 0) {
        connected = _client->connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD,
                                     lwt.c_str(), 1, true, "offline");
    } else {
        connected = _client->connect(MQTT_CLIENT_ID,
                                     lwt.c_str(), 1, true, "offline");
    }

    if (connected) {
        Serial.println("[MQTT] Conectado");
        _client->publish(lwt.c_str(), "online", true);
    }
}

void MQTTClient::publish(const MeterData& data) {
    if (!_client || !_client->connected()) return;

    // Publicar por fase
    for (int i = 0; i < 3; i++) {
        if (data.phase[i].valid) {
            publishPhase(i, data.phase[i]);
        }
    }

    // Publicar JSON agregado
    JsonDocument doc;
    doc["ts"] = data.isoTime;
    float totalP = 0;

    JsonArray phases = doc["phases"].to<JsonArray>();
    const char* names[] = {"L1", "L2", "L3"};
    for (int i = 0; i < 3; i++) {
        if (data.phase[i].valid) {
            JsonObject p = phases.add<JsonObject>();
            p["id"] = names[i];
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
    String topic = String(MQTT_TOPIC_BASE) + "/data";
    _client->publish(topic.c_str(), buffer);
}

void MQTTClient::publishPhase(int index, const PhaseData& phase) {
    char topic[64];
    char value[16];
    const char* names[] = {"L1", "L2", "L3"};
    const char* base = MQTT_TOPIC_BASE;

    snprintf(topic, sizeof(topic), "%s/%s/voltage", base, names[index]);
    snprintf(value, sizeof(value), "%.1f", phase.voltage);
    _client->publish(topic, value);

    snprintf(topic, sizeof(topic), "%s/%s/current", base, names[index]);
    snprintf(value, sizeof(value), "%.2f", phase.current);
    _client->publish(topic, value);

    snprintf(topic, sizeof(topic), "%s/%s/power", base, names[index]);
    snprintf(value, sizeof(value), "%.1f", phase.power);
    _client->publish(topic, value);

    snprintf(topic, sizeof(topic), "%s/%s/energy", base, names[index]);
    snprintf(value, sizeof(value), "%.3f", phase.energy);
    _client->publish(topic, value);

    snprintf(topic, sizeof(topic), "%s/%s/frequency", base, names[index]);
    snprintf(value, sizeof(value), "%.1f", phase.frequency);
    _client->publish(topic, value);

    snprintf(topic, sizeof(topic), "%s/%s/pf", base, names[index]);
    snprintf(value, sizeof(value), "%.2f", phase.powerFactor);
    _client->publish(topic, value);
}

void MQTTClient::publishAlarm(int phase, const String& type, float voltage) {
    if (!_client || !_client->connected()) return;

    char topic[64];
    snprintf(topic, sizeof(topic), "%s/alarm", MQTT_TOPIC_BASE);

    JsonDocument doc;
    doc["phase"] = phase + 1;
    doc["type"] = type;
    doc["voltage"] = voltage;

    char buffer[128];
    serializeJson(doc, buffer);
    _client->publish(topic, buffer, true);  // retain
}

bool MQTTClient::isConnected() const {
    return _client && _client->connected();
}

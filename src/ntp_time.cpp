#include "ntp_time.h"
#include <time.h>

void NTPTime::begin() {
    configTime(NTP_GMT_OFFSET, NTP_DST_OFFSET, NTP_SERVER);
    Serial.println("[NTP] Configurado - aguardando sync...");
}

void NTPTime::sync() {
    struct tm timeinfo;
    if (getLocalTime(&timeinfo, 5000)) {
        _synced = true;
        Serial.println("[NTP] Sincronizado");
    } else {
        Serial.println("[NTP] Falha na sincronizacao");
    }
}

String NTPTime::getISO8601() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo, 100)) {
        return "1970-01-01T00:00:00";
    }
    _synced = true;
    char buf[25];
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", &timeinfo);
    return String(buf);
}

bool NTPTime::isSynced() const {
    return _synced;
}

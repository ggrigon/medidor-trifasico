#include "sd_logger.h"
#include <SPI.h>

void SDLogger::begin() {
    SPI.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);

    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("[SD] Falha na inicializacao do cartao!");
        _ready = false;
        return;
    }

    Serial.printf("[SD] Cartao OK - Tamanho: %lluMB\n", SD.cardSize() / (1024 * 1024));

    if (!SD.exists(SD_LOG_DIR)) {
        SD.mkdir(SD_LOG_DIR);
    }

    _ready = true;
}

void SDLogger::log(const MeterData& data) {
    if (!_ready) return;

    String fileName = getFileName(data.isoTime);

    bool newFile = !SD.exists(fileName);
    File file = SD.open(fileName, FILE_APPEND);
    if (!file) {
        Serial.println("[SD] Erro ao abrir arquivo para escrita");
        return;
    }

    if (newFile) {
        writeHeader(file);
    }

    // timestamp
    file.print(data.isoTime);

    // dados das 3 fases
    for (int i = 0; i < 3; i++) {
        const PhaseData& p = data.phase[i];
        if (p.valid) {
            file.printf(",%.1f,%.2f,%.1f,%.3f,%.1f,%.2f",
                        p.voltage, p.current, p.power,
                        p.energy, p.frequency, p.powerFactor);
        } else {
            file.print(",,,,,, ");
        }
    }
    file.println();
    file.flush();
    file.close();
}

bool SDLogger::isReady() const {
    return _ready;
}

String SDLogger::getFileName(const String& isoTime) {
    // isoTime formato: "2026-02-21T14:30:00"
    String date = isoTime.substring(0, 10);  // "2026-02-21"
    return String(SD_LOG_DIR) + "/" + date + ".csv";
}

void SDLogger::writeHeader(File& file) {
    file.print("timestamp");
    const char* phases[] = {"L1", "L2", "L3"};
    const char* fields[] = {"V", "I", "P", "E", "F", "PF"};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            file.printf(",%s_%s", phases[i], fields[j]);
        }
    }
    file.println();
    file.flush();
}

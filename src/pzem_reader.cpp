#include "pzem_reader.h"

void PZEMReader::begin() {
    static HardwareSerial pzemSerial(2);

    _pzem[0] = new PZEM004Tv30(pzemSerial, PZEM_RX_PIN, PZEM_TX_PIN, PZEM_ADDR_L1);
    _pzem[1] = new PZEM004Tv30(pzemSerial, PZEM_RX_PIN, PZEM_TX_PIN, PZEM_ADDR_L2);
    _pzem[2] = new PZEM004Tv30(pzemSerial, PZEM_RX_PIN, PZEM_TX_PIN, PZEM_ADDR_L3);

    Serial.println("[PZEM] Inicializado - 3 fases em Serial2");
}

void PZEMReader::readAll(MeterData& data) {
    data.timestamp = millis();
    for (int i = 0; i < 3; i++) {
        if (!readPhase(i, data.phase[i])) {
            // Retry uma vez em caso de falha
            delay(10);
            readPhase(i, data.phase[i]);
        }
    }
}

bool PZEMReader::readPhase(int index, PhaseData& phase) {
    if (!_pzem[index]) {
        phase.valid = false;
        return false;
    }

    float v = _pzem[index]->voltage();
    float i = _pzem[index]->current();
    float p = _pzem[index]->power();
    float e = _pzem[index]->energy();
    float f = _pzem[index]->frequency();
    float pf = _pzem[index]->pf();

    if (isnan(v) || isnan(i) || isnan(p)) {
        phase.valid = false;
        return false;
    }

    phase.voltage     = v;
    phase.current     = i;
    phase.power       = p;
    phase.energy      = isnan(e) ? 0 : e;
    phase.frequency   = isnan(f) ? 0 : f;
    phase.powerFactor = isnan(pf) ? 0 : pf;
    phase.valid       = true;
    return true;
}

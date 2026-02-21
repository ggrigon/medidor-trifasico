#pragma once

#include <PZEM004Tv30.h>
#include "config.h"

class PZEMReader {
public:
    void begin();
    void readAll(MeterData& data);

private:
    PZEM004Tv30* _pzem[3] = {nullptr, nullptr, nullptr};
    bool readPhase(int index, PhaseData& phase);
};

#pragma once

#include <Arduino.h>
#include "config.h"

class NTPTime {
public:
    void begin();
    void sync();
    String getISO8601();
    bool isSynced() const;

private:
    bool _synced = false;
};

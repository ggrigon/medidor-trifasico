#pragma once

#include <SD.h>
#include "config.h"

class SDLogger {
public:
    void begin();
    void log(const MeterData& data);
    bool isReady() const;

private:
    bool _ready = false;
    String _currentFile;

    String getFileName(const String& isoTime);
    void writeHeader(File& file);
};

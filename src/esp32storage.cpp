#include "esp32storage.h"

ESP32Storage::ESP32Storage()
{
}

bool ESP32Storage::begin() {
    SPIFFS_INIT = SPIFFS.begin();
    if(SPIFFS_INIT)
        file = SPIFFS.open("/settings.bin", FILE_WRITE);
    return SPIFFS_INIT;
}

void ESP32Storage::load(Settings *settings)
{
    if(SPIFFS_INIT) {
        char *settingsBytes = reinterpret_cast<char *>(settings);
        if (file.size() != 0)
            file.readBytes(settingsBytes, sizeof(Settings));
    }
}

void ESP32Storage::save(Settings *settings)
{
    if(SPIFFS_INIT) {
        auto settingsBytes = reinterpret_cast<const uint8_t *>(settings);
        file.write(settingsBytes, sizeof(Settings));
    }
}

ESP32Storage::~ESP32Storage()
{
    file.close();
}

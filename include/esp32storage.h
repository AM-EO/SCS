#include <storage.h>
#include "SPIFFS.h"

class ESP32Storage : public Storage
{
private:
    File file;
    bool SPIFFS_INIT = false;
public:
    ESP32Storage();
    ~ESP32Storage();
    bool begin();
    void load(Settings *settings) override;
    void save(Settings *settings) override;
};
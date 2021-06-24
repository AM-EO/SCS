
#include "../Controller.h"
#include "settings.h"

class SettingsController: public Controller {
private:
    Settings* settings;
public:
    SettingsController(Settings*);
    void get() override;
    void post(const JsonObject &) override;
};
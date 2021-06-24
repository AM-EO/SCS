#include "../Controller.h"
#include "sensor.h"

class SensorController: public Controller {
private:
    Sensor* sensor;
public:
    SensorController(Sensor*);
    void get() override;
    void post(const JsonObject &) override;
};
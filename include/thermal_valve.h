#include "Arduino.h"
#include "motor.h"

class ThermalValve: public Motor {
public:
    ThermalValve();
    void drive(bool value) override;
};
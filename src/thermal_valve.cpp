#include "thermal_valve.h"

ThermalValve::ThermalValve()
{
    pinMode(14, OUTPUT);
}

void ThermalValve::drive(bool value)
{
    // Motor is connected to GPIO 14
    digitalWrite(14, value);
}
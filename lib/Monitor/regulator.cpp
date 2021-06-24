#include "regulator.h"

Regulator::Regulator() {}

void Regulator::setSetpoint(float setpoint)
{
    this->setpoint = setpoint;
}

float Regulator::getError()
{
    return error;
}

float Regulator::getSetpoint()
{
    return setpoint;
}
void Regulator::setSettings(Settings* settings) {
    this->settings = settings;
}
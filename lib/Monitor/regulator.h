#ifndef REGULATOR_H
#define REGULATOR_H
#include "math.h"
#include "clock.h"
#include "settings.h"
#pragma once

class Regulator
{
protected:
    float setpoint = 0;
    float error = 0;
    const int CONTROL_PRECISION = 1;
    Settings* settings;

public:
    Regulator();

    void setSetpoint(float setpoint);
    void setSettings(Settings*);

    float getError();
    float getSetpoint();

    int virtual control(float value) = 0;
};

#endif // REGULATOR_H

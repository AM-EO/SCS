#define MONITOR_H

#include <math.h>
#include <algorithm>
#include "settings.h"
#include "regulator.h"
#include "clock.h"
#include "motor.h"

#pragma once

class Monitor
{
private:
    void calculateControlMode();
    bool isEconomTime();

public:
    const Settings *settings;
    const Clock *clock;

    Regulator *regulator;
    Motor *motor;

    Monitor();
    void work(int sensorData);
};
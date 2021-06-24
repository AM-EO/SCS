#include "monitor.h"

Monitor::Monitor()
{
}

bool Monitor::isEconomTime()
{
    unsigned int currentTime = clock->getTime();
    if (settings->startTime < currentTime && currentTime < settings->endTime)
        return true;
    else
        return false;
}

void Monitor::calculateControlMode()
{
    if (isEconomTime())
        regulator->setSetpoint(settings->economTemp);
    else
        regulator->setSetpoint(settings->comfortTemp);
}

void Monitor::work(int sensorData)
{
    calculateControlMode();
    int value = regulator->control(sensorData);
    motor->drive(value);
}
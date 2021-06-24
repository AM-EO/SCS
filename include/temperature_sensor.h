#pragma once

#include "sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor : public Sensor
{
private:
    OneWire oneWire;
    DallasTemperature sensors;
    bool CONNECTED = false;

public:
    TemperatureSensor();
    void measure() override;
    void begin();
    bool isConnected();
};
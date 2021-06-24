#pragma once
#include "temperature_sensor.h"
#include "clock.h"
#include "ArduinoJson.h"

class PublishModel
{
private:
    TemperatureSensor *sensor;
    Clock *clock;

public:
    PublishModel(TemperatureSensor *sensor, Clock *clock);
    String get();
};
#include "sensor.h"

Sensor::Sensor()
{
}

void Sensor::setAddress(int address)
{
    this->address = address;
}
float Sensor::getData() const
{
    return data;
}

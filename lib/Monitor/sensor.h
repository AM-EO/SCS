#ifndef SENSOR_H
#define SENSOR_H
#pragma once

class Sensor
{
protected:
    float data = 0.0F;
    int address;

public:
    Sensor();
    void setAddress(int address);
    float getData() const;
    virtual void measure() = 0;
};

#endif // SENSOR_H

#include "temperature_sensor.h"

TemperatureSensor::TemperatureSensor()
{
}

void TemperatureSensor::begin() {
    // GPIO where the DS18B20 is connected to GPIO 4
    oneWire = OneWire(4);
    sensors = DallasTemperature(&oneWire);
    sensors.begin();
    sensors.setResolution(12);
}

void TemperatureSensor::measure()
{
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);
    CONNECTED = (temp == DEVICE_DISCONNECTED_F) ? false : true;
    if(CONNECTED) {
        data = temp;
    }
}

bool TemperatureSensor::isConnected() {
    return CONNECTED;
}
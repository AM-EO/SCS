#include "mqtt-service/PublishModel.h"

PublishModel::PublishModel(TemperatureSensor *sensor, Clock* clk)
{
    this->sensor = sensor;
    this->clock = clk;
}

String PublishModel::get()
{
    const size_t CAPACITY = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<CAPACITY> model;
    String output;
    model["data"] = sensor->getData();
    model["time"] = clock->getTime();
    serializeJson(model, output);
    return output;
}
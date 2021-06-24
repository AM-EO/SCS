#include "../../include/web-service/controllers/SensorController.h"

SensorController::SensorController(Sensor* sensor) {
    this->sensor = sensor;
}

void SensorController::get() {
    const int capacity = JSON_OBJECT_SIZE(4);
    StaticJsonDocument<capacity> model;
    model["tempData1"] = sensor->getData();
    model["tempData2"] = sensor->getData()-3.1;
    model["humData1"] = sensor->getData()+53.3;
    model["humData2"] = sensor->getData()+36.2;
    sendResponse(model.as<JsonVariant>());
}

void SensorController::post(const JsonObject &model) {
}
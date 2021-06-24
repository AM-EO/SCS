#include "../../include/web-service/controllers/ClockController.h"

ClockController::ClockController(Clock* clock) {
    this->clock = clock;
}

void ClockController::get() {
    const int capacity = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<capacity> model;
    model["time"] = clock->getTime();
    sendResponse(model.as<JsonVariant>());
}

void ClockController::post(const JsonObject &model) {
     clock->setTime(model["time"].as<int>());
}
#include "../../include/web-service/controllers/SettingsController.h"

SettingsController::SettingsController(Settings* settings) {
    this->settings = settings;
}

void SettingsController::get() {
    const int capacity = JSON_OBJECT_SIZE(4);
    StaticJsonDocument<capacity> model;
    model["comfortTemp"] = settings->getComfortTemp();
    model["economTemp"] = settings->getEconomTemp();
    model["startTime"] = settings->getStartTime();
    model["endTime"] = settings->getEndTime();
    sendResponse(model.as<JsonVariant>());
}

void SettingsController::post(const JsonObject &model) {
    settings->setComfortTemp(model["comfortTemp"].as<short>());
    settings->setEconomTemp(model["economTemp"].as<short>());
    settings->setStartTime(model["startTime"].as<int>());
    settings->setEndTime(model["endTime"].as<int>());
	settings->setDeadBand(model["deadband"].as<short>());
}
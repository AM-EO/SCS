#include "../../include/web-service/controllers/MQTTController.h"

MQTTController::MQTTController(MQTTConnection* mqttConnection) {
    this->mqttConnection = mqttConnection;
}

void MQTTController::get() {
    const int capacity = JSON_OBJECT_SIZE(6);
    StaticJsonDocument<capacity> model;
    model["server"] = mqttConnection->server;
    model["port"] = mqttConnection->port;
    model["user"] = mqttConnection->user;
    model["password"] = mqttConnection->password;
    model["eventTopic"] = mqttConnection->eventTopic;
    model["commandTopic"] = mqttConnection->commandTopic;
    sendResponse(model.as<JsonVariant>());
}

void MQTTController::post(const JsonObject &model) {
    mqttConnection->server = model["server"].as<String>();
    mqttConnection->port = model["port"].as<short>();
    mqttConnection->user = model["user"].as<String>();
    mqttConnection->password = model["password"].as<String>();
    mqttConnection->eventTopic = model["eventTopic"].as<String>();
    mqttConnection->commandTopic = model["commandTopic"].as<String>();
    mqttConnection->notify();
}
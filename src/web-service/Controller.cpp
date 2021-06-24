#include "../include/web-service/Controller.h"

void Controller::sendResponse(const JsonVariant &model)
{
    String output;
    serializeJson(model, output);
    request->send(200, "application/json", output);
}

void Controller::sendResponse(const String& model) {
    request->send(200, "application/json", model);
}
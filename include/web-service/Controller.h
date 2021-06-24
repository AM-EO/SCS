#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#pragma once

class Controller {
public:
    AsyncWebServerRequest *request = nullptr;
    void sendResponse(const JsonVariant &);
    void sendResponse(const String &);

    virtual void get() = 0;
    virtual void post(const JsonObject &) = 0;
};
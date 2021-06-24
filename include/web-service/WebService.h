#pragma once

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "Controller.h"

class WebService {
public:
    AsyncWebServer *server;
    void get(const char *uri, Controller* model);
    void post(const char *uri, Controller* model);
    void setGetAndPost(const char *uri, Controller* model);
};
#include "../include/web-service/WebService.h"

void WebService::get(const char *uri, Controller *controller)
{
    server->on(uri, HTTP_GET, [controller](AsyncWebServerRequest *request) {
        controller->request = request;
        controller->get();
    });
}

void WebService::post(const char *uri, Controller *controller)
{
    server->on(uri, HTTP_POST, [](AsyncWebServerRequest *request) {
        request->send(200);
    }, nullptr, [controller](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
        // максимальный размер объекта 10 пар ключ - значение
        DynamicJsonDocument doc(JSON_OBJECT_SIZE(10)); 
        deserializeJson(doc, (const char*)data);
        controller->request = request;
        controller->post(doc.as<JsonObject>());
    });
}

void WebService::setGetAndPost(const char *uri, Controller *controller) {
    post(uri, controller);
    get(uri, controller);
}
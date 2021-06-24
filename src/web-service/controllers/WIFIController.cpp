#include "../../include/web-service/controllers/WIFIController.h"
WIFIController::WIFIController(WIFIConnection *wifiConnection)
{
    this->wifiConnection = wifiConnection;
}

void WIFIController::get()
{
    String json = "[";
    int n = WiFi.scanComplete();
    if (n == -2)
    {
        WiFi.scanNetworks(true);
    }
    else if (n)
    {
        for (int i = 0; i < n; ++i)
        {
            if (i)
                json += ",";
            json += "{";
            json += "\"rssi\":" + String(WiFi.RSSI(i));
            json += ",\"ssid\":\"" + WiFi.SSID(i) + "\"";
            json += ",\"secure\":" + String(WiFi.encryptionType(i));
            json += "}";
        }
        WiFi.scanDelete();
        if (WiFi.scanComplete() == -2)
        {
            WiFi.scanNetworks(true);
        }
    }
    json += "]";
    sendResponse(json);
}

void WIFIController::post(const JsonObject &model)
{
    String ssid = model["ssid"].as<String>();
    String password = model["password"].as<String>();
    wifiConnection->connection(ssid, password);
    /*
    if (wifiConnection->connection(ssid, password))
    {
        response["status"] = "success";
    }
    else
    {
        response["status"] = "error";
    }
    sendResponse(response);*/
}
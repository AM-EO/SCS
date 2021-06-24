#include "../include/WIFIConnection.h"

bool WIFIConnection::connection(String ssid, String password)
{
    //IPAddress ip(192, 168, 4, 1);   
    //IPAddress gateway(192, 168, 1, 1);
    //IPAddress subnet(255, 255, 255, 0);

    //WiFi.config(ip, gateway, subnet);
    
    WiFi.begin(ssid.c_str(), password.c_str());
    return WiFi.status();
}

#include "system_init.h"
const char *ssid = "ESP-MODULE";
const char *password = "12345678";
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
const char *server_name = "www.dvoretskiy.com";

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  
  SPIFFS.begin();
  //storage.begin();
  sensor.begin();

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  //WiFi.begin("WIES", "kakdelawies");
  
  clk.setPeriod(1000);
  //storage.load(&settings);
  const byte DNS_PORT = 53;
  dnsServer.start(DNS_PORT, server_name, apIP);
  monitorConfigure();
  apiConfigure();
  serverConfigure();
  server.begin();
}

void loop()
{
  dnsServer.processNextRequest();
  I.ScanMessages();
  Led_1.AutoControl();
  Led_2.AutoControl();
  Pomp.AutoControl();
  Cull.AutoControl();
  clockDelay();
  sensor.measure();
  monitor.work(sensor.getData());
  mqttService.loop();
}


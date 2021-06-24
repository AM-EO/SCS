#include <Monitor.h>
#include "relay.h"
#include "thermal_valve.h"
#include "temperature_sensor.h"
#include "esp32storage.h"

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "SPIFFS.h"

#include "web-service/WebService.h"
#include "web-service/controllers/ClockController.h"
#include "web-service/controllers/MQTTController.h"
#include "web-service/controllers/SettingsController.h"
#include "web-service/controllers/WIFIController.h"
#include "web-service/controllers/SensorController.h"

#include "mqtt-service/MQTTService.h"
#include "mqtt-service/PublishModel.h"
#include "mqtt-service/MQTTConnection.h"
#include <DNSServer.h>



class Devices {
  public:
    String Tag;
    String Name;
    int Pin;
    bool General;
    bool Status;
    bool Now;
    unsigned long TimeInterval;
    unsigned long TimeWork;
    unsigned long TimeLast;
    unsigned long ModeTimeInterval[4] = {0,0,0,0} ;
    unsigned long ModeTimeWork[4] = {0,0,0,0};
    String DisplayBlockGen;
    String DisplayBlockStat;

    Devices(String _tag, String _name, int _pin,
            unsigned long _timeInterval,
            unsigned long _timeWork,
            unsigned long _timeLast, String _displayBlockGen,
            String _displayBlockStat) {
      Tag = _tag;
      Name = _name;
      Pin = _pin;
      TimeInterval = _timeInterval;
      TimeWork = _timeWork;
      ModeTimeInterval[0] = _timeInterval;
      ModeTimeWork[0] = _timeWork;
      TimeLast = millis();
      General = false;
      Status = false;
      Now = false;
      DisplayBlockGen = _displayBlockGen;
      DisplayBlockStat = _displayBlockStat;
      pinMode(Pin, OUTPUT);
      digitalWrite(Pin, HIGH);
    }

    void AutoControl() {
      if (General) {
        if (millis() > (TimeLast + TimeInterval)) {
          Status = true;
          comandToDisplay(DisplayBlockStat, Status); 
        }
        if (Status && !Now) {
          On();
        }
      }
      if (Now && (millis() > (TimeLast + TimeWork))) {
        Off();
      }
    }

    void Off() {
      digitalWrite(Pin, HIGH);
      TimeLast = millis();
      Now = false;
      Status = false;
      comandToDisplay(DisplayBlockStat, Status); 
    }

    void On() {
      digitalWrite(Pin, LOW);
      TimeLast = millis();
      Now = true;
      Status = true;
      comandToDisplay(DisplayBlockStat, Status); 
    }

    void comandToDisplay(String _displayBlock, bool _status) {
      Serial2.print(_displayBlock + (int)_status);
      for (int i = 0; i < 3; i++)
      {
        Serial2.write(0xff);
      }
    }

    void setGeneral(bool _flag) {
      General = _flag;
      comandToDisplay(DisplayBlockGen, General);
    }

    void setStatus(bool _flag) {
      Status = _flag;
      comandToDisplay(DisplayBlockStat, Status);
    }

    void commandHandler(String _comand) {
      switch (Tag.lastIndexOf(_comand)) {
        case 0:
          setGeneral(0);
          Off();
          break;
        case 4:
          setGeneral(1);
          break;
        case 8:
          setStatus(0);
          Off();
          break;
        case 12:
          setStatus(1);
          break;
        default:
          break;
      }
    }


};

class Interface {
  public:
    Devices *Led_1;
    Devices *Led_2;
    Devices *Pomp;
    Devices *Cull;

    Interface(Devices *_led_1,
              Devices *_led_2,
              Devices *_pomp,
              Devices *_cull) {
      Led_1 = _led_1;
      Led_2 = _led_2;
      Pomp = _pomp;
      Cull = _cull;
    }

    void ScanMessages() {
      String Data;
      while (Serial2.available()) {
        Data += char(Serial2.read());
        delay(10);
      }
      for (int i = 0; i < Data.length(); i += 4) {
        String comand = Data.substring(i, i + 4);
        if (Led_1->Tag.lastIndexOf(comand) >= 0) {
          //comand to dev
          Led_1->commandHandler(comand);
        }

        if (Led_2->Tag.lastIndexOf(comand) >= 0) {
          //comand to dev
          Led_2->commandHandler(comand);
        }

        if (Pomp->Tag.lastIndexOf(comand) >= 0) {
          //comand to dev
          Pomp->commandHandler(comand);
        }

        if (Cull->Tag.lastIndexOf(comand) >= 0) {
          //comand to dev
          Cull->commandHandler(comand);
        }

      }
    }
};



Devices Led_1("0x010x020x030x04", "Led_red", 13,
              7200000,
              76800000,
              -76800000, "page1.bt4.val=",
              "page1.bt0.val=");
Devices Led_2("0x0B0x0C0x0D0x0E", "Led_blue", 12,
              9600000,
              43200000,
              -43200000, "page1.bt5.val=",
              "page1.bt1.val=");
Devices Pomp("0x150x160x170x18", "Pomp", 11,
           7200000,
           76800000,
           -76800000, "page1.bt6.val=",
           "page1.bt2.val=");
Devices Cull("0x1F0x200x210x22", "Cull", 10,
         7200000,
         76800000,
         -76800000, "page1.bt7.val=",
         "page1.bt3.val=");

Interface I(&Led_1, &Led_2, &Pomp, &Cull);

void setMode(){
  
}


String getButtonData(){
  const size_t CAPACITY = JSON_OBJECT_SIZE(8);
  StaticJsonDocument<CAPACITY> model;
  String output;
  model["redNow"] = Led_1.Status;
  model["redGen"] = Led_1.General;
  model["blueNow"] = Led_2.Status;
  model["blueGen"] = Led_2.General;
  model["pompNow"] = Pomp.Status;
  model["pompGen"] = Pomp.General;
  model["cullNow"] = Cull.Status;
  model["cullGen"] = Cull.General;
  serializeJson(model, output);
  return output;
}




AsyncWebServer server{80};
WiFiClient espClient;
PubSubClient client(espClient);

Settings settings;
Relay relay;
Clock clk;
ThermalValve thermalValve;
TemperatureSensor sensor;
Monitor monitor;

WebService webService;
MQTTService mqttService;
MQTTConnection mqttConnection;
PublishModel publishModel(&sensor, &clk);

ClockController clockController(&clk);
SettingsController settingsController(&settings);
SensorController sensorController(&sensor);
MQTTController mqttController(&mqttConnection);
WIFIController wifiController(new WIFIConnection);

void apiConfigure()
{
  relay.setSettings(&settings);

  webService.server = &server;
  webService.setGetAndPost("/api/setup", &settingsController);
  webService.setGetAndPost("/api/mqtt", &mqttController);
  webService.setGetAndPost("/api/scanwifi", &wifiController);
  webService.setGetAndPost("/api/clock", &clockController);
  webService.get("/api/data", &sensorController);

  mqttService.mqttClient = &client;
  mqttService.setPublishModel(publishModel);
  mqttService.setConnection(mqttConnection);
}

void serverConfigure()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

   server.on("/favicon.png", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/favicon.png", "icon");
  });
  

  server.on("/css/app.3b72bb5a.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/app.3b72bb5a.css", "text/css");
  });

  server.on("/css/chunk-vendors.6f7ca633.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/chunk-vendors.6f7ca633.css", "text/css");
  });

  server.on("/js/app.6c47fb3f.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/app.6c47fb3f.js", "text/javascript");
  });

  server.on("/js/chunk-vendors.a5f96575.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/chunk-vendors.a5f96575.js", "text/javascript");
  });

  server.on("/api/buttons/getdata", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "application/json", getButtonData());
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
  });
  
  server.on("/api/mode", HTTP_GET, [](AsyncWebServerRequest *request) {
        setMode();
        request->send(200);
    });

  server.on("/api/buttons/rednowon", HTTP_GET, [](AsyncWebServerRequest *request) {
        Led_1.setStatus(1);
        request->send(200);
    });
  server.on("/api/buttons/rednowoff", HTTP_GET, [](AsyncWebServerRequest *request) {
        Led_1.setStatus(0);
        request->send(200);
    });
  server.on("/api/buttons/redgenon", HTTP_GET, [](AsyncWebServerRequest *request) {
        Led_1.setGeneral(1);
        request->send(200);
    });
  server.on("/api/buttons/redgenoff", HTTP_GET, [](AsyncWebServerRequest *request) {
        Led_1.setGeneral(0);
        request->send(200);
    });


  server.on("/api/buttons/bluenowon", HTTP_GET, [](AsyncWebServerRequest *request) {
        Led_2.setStatus(1);
        request->send(200);
    });
  server.on("/api/buttons/bluenowoff", HTTP_GET, [](AsyncWebServerRequest *request) {
        Led_2.setStatus(0);
        request->send(200);
    });
  server.on("/api/buttons/bluegenon", HTTP_GET, [](AsyncWebServerRequest *request) {
        Led_2.setGeneral(1);
        request->send(200);
    });
  server.on("/api/buttons/bluegenoff", HTTP_GET, [](AsyncWebServerRequest *request) {
        Led_2.setGeneral(0);
        request->send(200);
    });


    server.on("/api/buttons/pompnowon", HTTP_GET, [](AsyncWebServerRequest *request) {
        Pomp.setStatus(1);
        request->send(200);
    });
  server.on("/api/buttons/pompnowoff", HTTP_GET, [](AsyncWebServerRequest *request) {
        Pomp.setStatus(0);
        request->send(200);
    });
  server.on("/api/buttons/pompgenon", HTTP_GET, [](AsyncWebServerRequest *request) {
        Pomp.setGeneral(1);
        request->send(200);
    });
  server.on("/api/buttons/pompgenoff", HTTP_GET, [](AsyncWebServerRequest *request) {
        Pomp.setGeneral(0);
        request->send(200);
    });


    server.on("/api/buttons/cullnowon", HTTP_GET, [](AsyncWebServerRequest *request) {
        Cull.setStatus(1);
        request->send(200);
    });
  server.on("/api/buttons/cullnowoff", HTTP_GET, [](AsyncWebServerRequest *request) {
        Cull.setStatus(0);
        request->send(200);
    });
  server.on("/api/buttons/cullgenon", HTTP_GET, [](AsyncWebServerRequest *request) {
        Cull.setGeneral(1);
        request->send(200);
    });
  server.on("/api/buttons/cullgenoff", HTTP_GET, [](AsyncWebServerRequest *request) {
        Cull.setGeneral(0);
        request->send(200);
    });



  
  
}

void monitorConfigure()
{
  monitor.settings = &settings;
  monitor.regulator = &relay;
  monitor.clock = &clk;
  monitor.motor = &thermalValve;
}

void clockDelay()
{
  delay(clk.getPeriod());
  clk.tick();
}






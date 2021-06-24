#include "../include/mqtt-service/MQTTService.h"

bool MQTTService::reconnect()
{
    //String mqttClientId = "ESPmqttClient-";
    //mqttClientId += String(random(0xffff), HEX);
    //, connection->user.c_str(), connection->password.c_str()
    mqttClient->connect("espclient");
    return mqttClient->connected();
}

void MQTTService::setConnection(MQTTConnection &connection)
{
    this->connection = &connection;
    this->connection->attach(this);
}

void MQTTService::setPublishModel(PublishModel &publishModel)
{
    this->publishModel = &publishModel;
}

void MQTTService::update()
{
    if (mqttClient->connected())
    {
        mqttClient->disconnect();
    }
    mqttClient->setServer(connection->server.c_str(), connection->port);
    Serial.print(connection->server.c_str());
}

void MQTTService::loop()
{
    if (!connection->server.isEmpty() && connection->port != 0)
    {
        if (!mqttClient->connected())
        {
            long now = millis();
            if (now - lastReconnectAttempt > 5000)
            {
                lastReconnectAttempt = now;
                // Attempt to reconnect
                if (reconnect())
                {
                    lastReconnectAttempt = 0;
                }
            }
        }
        else
        {
            // mqttClient connected
            mqttClient->loop();
            publish();
        }
    }
}

void MQTTService::publish()
{
    String message = publishModel->get();
    mqttClient->publish(connection->eventTopic.c_str(), message.c_str());
}
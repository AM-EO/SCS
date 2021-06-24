#pragma once

#include <PubSubClient.h>
#include "PublishModel.h"
#include "MQTTConnection.h"
#include "../Observer.h"


class MQTTService : public Observer
{
private:
    long lastReconnectAttempt = 0;
    MQTTConnection *connection = nullptr;
    PublishModel *publishModel = nullptr;
    void publish();
    bool reconnect();
public:
    PubSubClient* mqttClient;
    void loop();
    void setConnection(MQTTConnection &);
    void setPublishModel(PublishModel &);
    void update() override;
};
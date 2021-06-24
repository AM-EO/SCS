#pragma once
#include "../Subject.h"

class MQTTConnection : public Subject {
public:
    String server;
    short port = 0;
    String user;
    String password;
    String eventTopic;
    String commandTopic;
};
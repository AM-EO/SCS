#include "../Controller.h"
#include "../../mqtt-service/MQTTConnection.h"

class MQTTController: public Controller {
private:
    MQTTConnection* mqttConnection;
public:
    MQTTController(MQTTConnection*);
    void get() override;
    void post(const JsonObject &) override;
};

#include "../Controller.h"
#include "../../WIFIConnection.h"

class WIFIController: public Controller {
private:
    WIFIConnection* wifiConnection;
public:
    WIFIController(WIFIConnection*);
    void get() override;
    void post(const JsonObject &) override;
};
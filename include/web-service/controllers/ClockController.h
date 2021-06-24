#include "../Controller.h"
#include "clock.h"

class ClockController: public Controller {
private:
    Clock* clock;
public:
    ClockController(Clock*);
    void get() override;
    void post(const JsonObject &) override;
};
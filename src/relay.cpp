#include "relay.h"
#include <cstdlib>

Relay::Relay() {}

int Relay::control(float value)
{
    error = setpoint - value;
    short deadband = settings->getDeadBand();

    if (fabsf(error) > deadband && error > 0)
        return 1;
    else
        return 0;
}

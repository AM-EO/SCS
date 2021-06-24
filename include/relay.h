#ifndef RELAY_H
#define RELAY_H

#include "regulator.h"

class Relay : public Regulator
{
public:
    Relay();
    int control(float value) override;
};

#endif // RELAY_H

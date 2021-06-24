#include "settings.h"
#pragma once

class Storage
{
public:
    Storage(){};
    virtual void load(Settings *settings) = 0;
    virtual void save(Settings *settings) = 0;
};
#include "settings.h"

Settings::Settings()
{
}

void Settings::setStartTime(int startTime)
{
    if (startTime >= LOW_TIME_LIMIT)
    {
        this->startTime = startTime;
    }
}

void Settings::setEndTime(int endTime)
{
    if (endTime <= HIGH_TIME_LIMIT)
    {
        this->endTime = endTime;
    }
}

void Settings::setEconomTemp(short economTemp)
{
    if (economTemp >= LOW_TEMP_LIMIT)
    {
        this->economTemp = economTemp;
    }
}

void Settings::setComfortTemp(short comfortTemp)
{
    if (comfortTemp <= HIGH_TEMP_LIMIT)
    {
        this->comfortTemp = comfortTemp;
    }
}

void Settings::setDeadBand(short deadBand)
{
    this->deadBand = deadBand;
}

int Settings::getStartTime() const
{
    return startTime;
}

int Settings::getEndTime() const
{
    return endTime;
}

short Settings::getEconomTemp() const
{
    return economTemp;
}

short Settings::getComfortTemp() const
{
    return comfortTemp;
}

short Settings::getDeadBand() const 
{
    return deadBand;
}
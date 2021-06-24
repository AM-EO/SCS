#include "clock.h"

Clock::Clock()
{
}

void Clock::tick()
{
    time += period;
    if (time >= MAX_TIME)
    {
        time = time - MAX_TIME;
    }
}

void Clock::setTime(int time)
{
    if(time <= MAX_TIME) {
        this->time = time;
    }
}

void Clock::setPeriod(int period)
{
    this->period = period;
}

int Clock::getPeriod() const
{
    return period;
}

int Clock::getTime() const
{
    return time;
}

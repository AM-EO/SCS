#ifndef CLOCK_H
#define CLOCK_H
#pragma once

class Clock
{
private:
    int time = 0;
    int period = 0;
    
public:
    const int MAX_TIME = 86400000;

    Clock();

    void tick();

    void setTime(int time);
    void setPeriod(int period);

    int getTime() const;
    int getPeriod() const;
};

#endif // CLOCK_H

#pragma once

#define LOW_TEMP_LIMIT 5
#define HIGH_TEMP_LIMIT 25

#define LOW_TIME_LIMIT 0
#define HIGH_TIME_LIMIT 86400000

class Settings
{

friend class Monitor;

private:
    int startTime = 43200000;
    int endTime = 64800000;
    int time = 0;
    short economTemp = 10;
    short comfortTemp = 20;
    short deadBand = 1;
public:
    Settings();
    void setStartTime(int start);
    void setEndTime(int end);
    void setEconomTemp(short e);
    void setComfortTemp(short c);
    void setDeadBand(short deadBand);

    int getStartTime() const;
    int getEndTime() const;
    short getEconomTemp() const;
    short getComfortTemp() const;
    short getDeadBand() const;
};

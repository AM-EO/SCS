#pragma once
#include "Observer.h"

class Subject {
private:
    Observer* observer;
public:
    void attach(Observer*);
    void detach(Observer*);
    void notify();
};
#ifndef MOTOR_H
#define MOTOR_H
#pragma once

class Motor
{
public:
    void virtual drive(bool value) = 0;
};

#endif // MOTOR_H

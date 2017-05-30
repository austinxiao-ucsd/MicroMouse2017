#ifndef RIGHT_MOTOR_H
#define RIGHT_MOTOR_H
#include "mbed.h"
class RightMotor {
public:
    RightMotor();

    // Define speed as float value between -1.0 and 1.0
    void speed(float speed);
    
    void stop(void);
    
    // Override operator for setting motor speed
    void operator = (float speed) {
        RightMotor::speed(speed);
    }
    
#endif
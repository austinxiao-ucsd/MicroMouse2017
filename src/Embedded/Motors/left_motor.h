#ifndef LEFT_MOTOR_H
#define LEFT_MOTOR_H
#include "mbed.h"
class LeftMotor {
public:
    LeftMotor();
    
    // Define speed as float value between -1.0 and 1.0
    void speed(float speed);
    
    // Stop the motor without breaking mechanism
    void stop(void);
    
    // Override operator for setting motor speed
    void operator = (float speed) {
        LeftMotor::speed(speed);
    }
    
private:
    //float curr_speed;
};

#endif
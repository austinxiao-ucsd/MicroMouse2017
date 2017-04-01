#ifndef MOTOR_H
#define MOTOR_H
#include "mbed.h"

class Motor {
public:
    Motor(PinName pwm, PinName dir);
    
    // Define speed as float value between -1.0 and 1.0
    void speed(float speed);
    
    // Stop the motor without breaking mechanism
    void stop(void);
    
    // Override operator for setting motor speed
    void operator = (float speed) {
        Motor::speed(speed);
    }
    
    // Getter method to retrieve the current speed
    float read(){
        return curr_speed;
    }
    
private:
    volatile float curr_speed;
    PwmOut pwm_pin;
    DigitalOut dir;
};

// Declaring as extern to enable global scope
extern Motor leftMotor;
extern Motor rightMotor;

#endif
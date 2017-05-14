#ifndef LEFT_MOTOR_H
#define LEFT_MOTOR_H
#include "mbed.h"
class LeftMotor {
public:
    LeftMotor();
    
    // Define speed as float value between -1.0 and 1.0
    void speed(float speed);
    
    void inv_dir(bool dir);
    // Stop the motor without breaking mechanism
    void stop(void);
    
    void set_period(float period);
    
    // Override operator for setting motor speed
    void operator = (float speed) {
        LeftMotor::speed(speed);
    }
    
    // Getter method to retrieve the current speed
    float read(){
        return curr_speed;
    }
    
private:
    float curr_speed;
};

#endif
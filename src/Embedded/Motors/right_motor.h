#ifndef RIGHT_MOTOR_H
#define RIGHT_MOTOR_H
#include "mbed.h"
class RightMotor {
public:
    RightMotor();
    
    // Define speed as float value between -1.0 and 1.0
    void speed(float speed);
    
    void inv_dir(bool dir);
    // Stop the motor without breaking mechanism
    void stop(void);
    
    void set_period(float period);
    
    // Override operator for setting motor speed
    void operator = (float speed) {
        RightMotor::speed(speed);
    }
    
    // Getter method to retrieve the current speed
    float read(){
        return curr_speed;
    }
    
private:
    float curr_speed;
};

#endif
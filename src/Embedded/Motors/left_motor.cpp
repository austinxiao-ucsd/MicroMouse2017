#include "left_motor.h"
PwmOut motor_left_sig(PB_7);
DigitalOut dir_left(PB_6);


LeftMotor::LeftMotor() {
    curr_speed = 0;
    dir_left = 0;
    motor_left_sig.period(0.001);
}

//Sets motor speed
void LeftMotor::speed(float speed) {
    curr_speed = speed;
    motor_left_sig.write(speed);
}

void LeftMotor::inv_dir(bool dir){
    if(dir == 1)
        dir_left = 1;
    else
        dir_left = 0;
}

void LeftMotor::set_period(float period) {
    motor_left_sig.period(period);
}

//Sets motor speed to 0
void LeftMotor::stop() {
    motor_left_sig.write(0);
}
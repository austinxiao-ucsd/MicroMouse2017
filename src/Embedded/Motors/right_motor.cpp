#include "right_motor.h"
PwmOut motor_right_sig(PB_9);
DigitalOut dir_right(PB_8);

RightMotor::RightMotor() {
    curr_speed = 0;
    dir_right = 1;
    motor_right_sig.period(0.001);
}

//Sets motor speed
void RightMotor::speed(float speed) {
    dir_right = 1;
    curr_speed = speed;
    motor_right_sig.write(speed);
}

void RightMotor::inv_dir(bool dir){
    if(dir == 1)
        dir_right = 1;
    else
        dir_right = 0;
}

void RightMotor::set_period(float period) {
    motor_right_sig.period(period);
}

//Sets motor speed to 0
void RightMotor::stop() {
    dir_right = 0;
    motor_right_sig.write(0);
}
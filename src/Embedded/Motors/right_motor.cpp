#include "right_motor.h"
PwmOut motor_channelA(PB_9);
PwmOut motor_channelB(PB_8);

RightMotor::RightMotor() {
 
    motor_channelA.period_us(50);
    motor_channelB.period_us(50);
}

//Sets motor speed
void RightMotor::speed(float speed) {

    if(speed < 0.0f){
        motor_channelA.write(-speed/100);
        motor_channelB.write(0);
    }
    else{
        motor_channelB.write(speed/100);
        motor_channelA.write(0); 
    }
}

//void RightMotor::set_period(float period) {
//    motor_right_sig.period(period);
//}

//Sets motor speed to 0
void RightMotor::stop() {
    
    motor_channelB.write(0);
    motor_channelA.write(0);
}
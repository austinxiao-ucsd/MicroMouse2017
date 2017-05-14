#include "left_motor.h"
PwmOut leftmotor_channelA(PB_6);
PwmOut leftmotor_channelB(PB_7);

LeftMotor::LeftMotor() {
 
    leftmotor_channelA.period_us(50);
    leftmotor_channelB.period_us(50);
}

//Sets motor speed
void LeftMotor::speed(float speed) {

    if(speed < 0.0f){
        leftmotor_channelA.write(-speed/100);
        leftmotor_channelB.write(0);
    }
    else{
        leftmotor_channelB.write(speed/100);
        leftmotor_channelA.write(0); 
    }
}

//void LeftMotor::set_period(float period) {
//    motor_right_sig.period(period);
//}

//Sets motor speed to 0
void LeftMotor::stop() {
    
    leftmotor_channelB.write(0);
    leftmotor_channelA.write(0);
}
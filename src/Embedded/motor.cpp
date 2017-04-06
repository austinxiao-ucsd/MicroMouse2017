#include "motor.h"
const int FORWARD = 1;
const int BACKWARD = 0;
const int ONE_MILLISECOND = 0.001;

Motor::Motor(PinName _pwm_pin, PinName _dir):
        pwm_pin(_pwm_pin), dir(_dir){
    pwm_pin.period(ONE_MILLISECOND);
    pwm_pin = 0; 
    dir = 0;
    curr_speed = 0;
}

//Sets motor speed
void Motor::speed(float speed) {
    if (speed < 0.0f){ //Backwards
        if (speed < -1.0f){
            speed = -1.0f;
        }
        dir = FORWARD;
        pwm_pin = curr_speed = speed + 1.0f; // Inverts it so 1 is off and 0 is on
    } else { //Forwards   
        dir = BACKWARD;
        pwm_pin = curr_speed = speed;
    }
}

//Sets motor speed to 0
void Motor::stop() {
    speed(0);
}
#include "mbed.h"
#include "ir_sensor.h"

float IRSensor::readIR() {
    float sum;
    _enable = 1;
    wait_us(60);
    sum = _input.read();
    _enable = 0;
    wait_us(60);
    //Each duration takes 100us, 5 times = 0.5ms
//    for (int i = 0; i < 5; i++)
//    {
//        //Turn on IR LED tx
//        _enable = 1;
//        //Wait for capacitor to fire, 10us
//        wait_us(60);
//        last_read[i] = _input.read_u16();
//        if (i){
//            sum += last_read[i];
//        }
//        //Wait 5us for turning off IR LED tx
//        _enable = 0;
//        //Wait 85us for turning on IR LED tx
//        wait_us(60);
//    }
//    sum /= 80;
//    value = sum;
    return sum;
}

//float IRSensor::cell_dist(){
//    return readIR() / 18;
//}
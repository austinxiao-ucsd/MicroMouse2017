#include "mbed.h"
#include "ir_sensor.h"

float IRSensor::readIR() {
    float sum = 0;
    //Each duration takes 100us, 5 times = 0.5ms
    for (int i = 0; i < 5; i++)
    {
        //Turn on IR LED tx
        _enable = 1;
        //Wait for capacitor to fire, 10us
        wait_us(6);
        last_read[i] = _input.read();
        if (i){
            sum += last_read[i];
        }
        //Wait 5us for turning off IR LED tx
        _enable = 0;
        //Wait 85us for turning on IR LED tx
        wait_us(75);
    }
    sum /= 4;
    value = sum;
    return value;
}

float IRSensor::cell_dist(){
    return readIR() / 18;
}
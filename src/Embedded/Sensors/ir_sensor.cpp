#include "mbed.h"
#include "ir_sensor.h"

float IRSensor::readIR() {
    float value;
    _enable = 1;
    wait_us(60);
    value = _input.read();
    _enable = 0;
    wait_us(60);
    
    return value;
    
    /*
    float sensor_arr [5];
    //Each duration takes 100us, 5 times = 0.5ms
    for (int i = 0; i < 5; i++)
    {
        float value;
        _enable = 1;
        wait_us(30);
        sensor_arr[i] = _input.read();
        _enable = 0;
        wait_us(30);
    }
    float sum = 0.0f;
    for (int i = 2; i < 5; i++) {
        sum += sensor_arr[i];
    }
    
    return sum/3;*/
}

//float IRSensor::cell_dist(){
//    return readIR() / 18;
//}
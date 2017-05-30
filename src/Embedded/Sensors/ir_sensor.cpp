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
}

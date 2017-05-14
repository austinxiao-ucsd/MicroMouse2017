#ifndef IR_H
#define IR_H
#include "mbed.h"
extern Serial pc;

class IRSensor {
public:
    DigitalOut _enable;
    AnalogIn _input;
    volatile float value; 

    float last_read[5];    
    IRSensor(PinName enable, PinName input) : _enable(enable), _input(input){}

    // Calculate an estimated IR value
    float readIR();

    //Get the number of cells away wall is
    float cell_dist();

    //Shorthand for read()
    operator float() {
        return readIR();
    }
};

extern IRSensor rightIR;
extern IRSensor rightDiagonalIR;
extern IRSensor rightFrontIR;
extern IRSensor leftFrontIR;
extern IRSensor leftDiagonalIR;
extern IRSensor leftIR;


#endif
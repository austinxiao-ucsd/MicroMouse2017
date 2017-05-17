#ifndef PIN_ASSIGNMENTS_H
#define PIN_ASSIGNMENTS_H

#include "encoder.h"
#include "ir_sensor.h"

// Encoders
Encoder leftEncoder(PC_9, PC_8);
Encoder rightEncoder(PA_1, PA_0);

IRSensor leftDiagonalIR(PC_7, PC_4); //emmiter and receiver DIAG LEFT sensor
IRSensor rightDiagonalIR(PB_1, PA_5); //emmiter and receiver DIAG RIGHTsensor

IRSensor rightFrontIR(PB_0, PA_6);

// IRSensors 
//IRSensor leftIR(PC_7, PC_5);
//IRSensor rightIR(PB_10, PA_4);
/*
IRSensor rightDiagonalIR(PA_8, PA_5);
IRSensor rightFrontIR(PB_0, PA_6);
IRSensor leftFrontIR(PB_1, PA_7);
IRSensor leftDiagonalIR(PC_6, PC_4);
*/
#endif
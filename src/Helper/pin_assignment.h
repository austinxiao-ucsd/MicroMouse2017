#ifndef PIN_ASSIGNMENTS_H
#define PIN_ASSIGNMENTS_H

#include "encoder.h"
#include "ir_sensor.h"

// Encoders
Encoder leftEncoder(PC_9, PC_8);
Encoder rightEncoder(PA_1, PA_0);

IRSensor leftDiagonalIR(PC_7, PC_4); //emmiter and receiver DIAG LEFT sensor
IRSensor rightDiagonalIR(PB_1, PA_5); //emmiter and receiver DIAG RIGHTsensor

IRSensor rightFrontIR(PB_10, PA_6);
IRSensor leftFrontIR(PC_6, PA_7);

#endif
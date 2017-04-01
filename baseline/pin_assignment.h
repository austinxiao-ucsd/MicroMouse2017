#ifndef PIN_ASSIGNMENTS_H
#define PIN_ASSIGNMENTS_H

#include "motor.h"
#include "encoder.h"
#include "ir_sensor.h"

AnalogIn battery(PA_3);
Serial pc(PA_9, PA_10);

// Motor
Motor leftMotor(PC_8, PC_7);
Motor rightMotor(PB_9, PB_8);

// Encoders
Encoder leftEncoder(PB_3, PB_4);
Encoder rightEncoder(PB_7, PB_6);

// IRSensors 
IRSensor leftIR(PC_3, PC_5);
IRSensor rightIR(PH_0, PA_4);
IRSensor rightDiagonalIR(PH_1, PA_5);
IRSensor rightFrontIR(PC_0, PA_6);
IRSensor leftFrontIR(PC_1, PA_7);
IRSensor leftDiagonalIR(PC_4, PC_2);

#endif
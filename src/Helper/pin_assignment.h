#ifndef PIN_ASSIGNMENTS_H
#define PIN_ASSIGNMENTS_H

#include "motor.h"
#include "encoder.h"
#include "ir_sensor.h"

// Motor
Motor leftMotor(PB_7, PB_6);
Motor rightMotor(PB_9, PB_8);

// Encoders
Encoder leftEncoder(PC_9, PC_8);
Encoder rightEncoder(PA_1, PA_0);

// IRSensors 
IRSensor leftIR(PC_7, PC_5);
IRSensor rightIR(PB_10, PA_4);
IRSensor rightDiagonalIR(PA_8, PA_5);
IRSensor rightFrontIR(PB_0, PA_6);
IRSensor leftFrontIR(PB_1, PA_7);
IRSensor leftDiagonalIR(PC_6, PC_4);

#endif
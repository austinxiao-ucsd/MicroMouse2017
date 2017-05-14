#ifndef IO_MODULES_H
#define IO_MODULES_H
#include "mbed.h"

// Battery Debugger Interface
AnalogIn battery(PA_3);
Serial pc(PA_9, PA_10);

// Led Debugger Interface
DigitalOut led_1(PB_12);
DigitalOut led_2(PB_13);
DigitalOut led_3(PB_14);
DigitalOut led_4(PB_15);

// System io
Serial serial (PA_9, PA_10);

#endif
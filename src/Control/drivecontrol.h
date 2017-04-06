#ifndef __DRIVE_CONTROL_H__
#define __DRIVE_CONTROL_H__
#include "motor.h"

/**
* Control mouse movements.
* - PID Control based on sensor readings.
* - Output PWM signals to motors based on feedback loop.
* - Provides directional signals to the main control loop.
*/
class DriveControl {

public:
    int y;
    int x;
    DriveControl (int start_x, int start_y);
    ~DriveControl();
    
    int get_next_direction() {
        // TODO
        // Check relative pos of next_cell and curr_cell
        return 0;
    }
    
    // Stops both motors. Assume no coasting.
    void stop() {
        leftMotor = 0;
        rightMotor = 0;
    }
    
    void drive_one_forward();
    
    void turn();
    
    void turn_left();
    
    void turn_right();
};
#endif
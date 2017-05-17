#ifndef __DRIVE_CONTROL_H__
#define __DRIVE_CONTROL_H__

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
    //float total_error;
    DriveControl (int start_x, int start_y);
    ~DriveControl();
    
    int get_next_direction();
    
    int get_next_state(int state);
    
    // Stops both motors. Assume no coasting.
    void stop();
    
    void getEncoder();
    
    void drive_forward();
    
    void turn();
    
    void turn_left();
    
    void turn_right();
    
    void turn_around();
    
    void drive(float speed);
    
    bool has_front_wall();
    
    bool has_right_wall();
    
    bool has_left_wall();
};
#endif
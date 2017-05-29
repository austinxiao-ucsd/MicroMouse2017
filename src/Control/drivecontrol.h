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
    DriveControl () {};
    
    ~DriveControl();
    
    int get_next_direction();
    
    // Stops both motors. Assume no coasting.
    void stop();
    
    void print_serial_ports();
    
    void drive_forward();
    
    void turn();
    
    void turn_left();
    
    void turn_right();
    
    void turn_around();
    
    void drive(float speed);
    
    bool has_front_wall();
    
    bool has_right_wall();
    
    bool has_left_wall();
    
    void resetEncoders();
    
    void clear_pid();
    
    void set_wall_follower_speed();
    
    void set_wall_follower_sensor_thres();
    
    bool should_finish_turn_right();
    
    bool right_wall_pid_debug();
    
    bool should_finish_turn_left ();
    
    bool should_stop_drive_forward();
    
    bool should_finish_turn_around();
    
    bool should_finish_drive_forward();
};
#endif
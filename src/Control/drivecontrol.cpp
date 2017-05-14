#include "drivecontrol.h"
#include "Cell.h"
#include "ir_sensor.h"
#include "left_motor.h"
#include "right_motor.h"

// Bit to specify debugging mode
const bool DEBUG = false;
// Define states for debugging the mouse hardware
const int DRIVE = 1, TURN = 2, STOP = 4;
const int SENSOR_THRESHOLD = 12;
LeftMotor * leftMotor;
RightMotor * rightMotor;
Cell * curr_cell;

namespace pid_controller
{
    float motor_speed;
    float LEFT_WALL_THRES = 0.89f, RIGHT_WALL_THRES = 0.91f;
    float SENSOR_ERROR_OFFSET = 0.02f;
    
    float error_p = 0.0f, old_error_p = 0.0f, error_d = 0.0f;
    float total_error;
    float P = 0.02f, D = 0.01f;
    bool has_left_wall = leftIR.readIR() > LEFT_WALL_THRES;
    bool has_right_wall = rightIR.readIR() > RIGHT_WALL_THRES;
    
    
    void start_pid() {
        if (has_left_wall && has_right_wall) {
            error_p = rightIR - leftIR - SENSOR_ERROR_OFFSET;
            error_d = error_p - old_error_p;    
        }
        else if (has_left_wall) {
            error_p = 2 * (LEFT_WALL_THRES - leftIR.readIR());
            error_d = error_p - old_error_p;
        }
        else if (has_right_wall) {
            error_p = 2 * (rightIR.readIR() - RIGHT_WALL_THRES);
            error_d = error_p - old_error_p;
        }
        else if (!has_left_wall && !has_right_wall) {
            error_p = 0;
            error_d = 0;
        }
        total_error = P * error_p + D*error_d;
        old_error_p = error_p;
        // if (DEBUG) { leftMotor->speed(0.15f); rightMotor->speed(0.85f); }
        leftMotor -> speed(0.15f - total_error);
        rightMotor -> speed(0.85f + total_error);
    }    
}

// Currently only have the x, y position fields for
// each cell.
DriveControl::DriveControl (int start_x, int start_y) {
    curr_cell = new Cell (start_x, start_y);
    leftMotor= new LeftMotor();
    rightMotor = new RightMotor();
}

// Defines the next cell to traverse.
Cell * next_cell() {
    // cell should get the reference from the Algorithm class.
    // Cell * cell;
    return curr_cell;
}

void DriveControl::turn_left() {
    // TODO: Add PID Control
}

int DriveControl::get_next_direction() {
    // TODO: Define the direction based on heuristic eval. 
    return 1;   
}

int DriveControl::get_next_state(int state) {
    // Simply drives the mouse for testing
    return DRIVE;
    
    /*
    // Front wall threshold is set to 12
    if (this->DriveControl::has_front_wall()) {
        return DRIVE;
    }
    
    if (!has_right_wall() || !has_left_wall()) {
     //   return TURN;
    }
    // Add Another Check for abnormal state
    return DEBUG;   */ 
}

void DriveControl::turn_right() {
    // TODO: Add PID Control
    
}

void DriveControl::stop() {
    leftMotor->stop();
    rightMotor->stop(); 
}

void DriveControl::drive_one_forward() {
    if (DEBUG) { leftMotor->speed(0.15f); rightMotor->speed(0.85f); }
    else {
        int count = 0;
        while (count != 10) {
            pid_controller::start_pid();
            count ++;
        }
    }
}

void start_pid() {
    
}

bool DriveControl::has_front_wall() {
    return rightFrontIR < SENSOR_THRESHOLD && leftFrontIR < SENSOR_THRESHOLD;
}

bool DriveControl::has_left_wall() {
    return leftIR < SENSOR_THRESHOLD;
}

bool DriveControl::has_right_wall() {
    return rightIR < SENSOR_THRESHOLD;
}

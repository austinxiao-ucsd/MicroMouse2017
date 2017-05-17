#include "drivecontrol.h"
#include "Cell.h"
#include "ir_sensor.h"
#include "left_motor.h"
#include "right_motor.h"
#include "pin_assignment.h"

IRSensor leftIR(PA_8, PC_5);
IRSensor rightIR(PB_0, PA_4);
//Encoder rightEncoder(PA_1, PA_0);
//Encoder leftEncoder(PC_9, PC_8);
LeftMotor * leftMotor;
RightMotor * rightMotor;
Cell * curr_cell;
Serial pc(PA_9, PA_10);

// Define states for debugging the mouse hardware
const int DRIVE = 0; //, TURN = 2, STOP = 4;
const int TURN_LEFT = 0, TURN_RIGHT = 1, TURN_AROUND = 2;

// Sensor offsets
float FRONT_SENSOR_THRESHOLD = 0.90f, SENSOR_ERROR_OFFSET = 0.0f;
float LEFT_WALL_THRES = 0.46f, RIGHT_WALL_THRES = 0.21f;
const int SENSOR_THRESHOLD = 12;

// Motor speed offsets
float left_speed, right_speed, motor_speed;
float MOTOR_BASE_SPEED = 15.0f;

namespace pid_controller { 
    // PID Constants
    float error_p = 0.0f, old_error_p = 0.0f, old_error_d = 0.0f, error_d = 0.0f;
    float total_error = 0.0f;
    float P = 18.0f, D = 3.0f;
    
    void navigate() {
        bool has_left_wall = leftDiagonalIR.readIR() > LEFT_WALL_THRES;
        bool has_right_wall = rightDiagonalIR.readIR() > RIGHT_WALL_THRES;

        if (has_left_wall && has_right_wall) {
            if (rightDiagonalIR - RIGHT_WALL_THRES < 0) {
                error_p = rightDiagonalIR - RIGHT_WALL_THRES;
            }
            else if (leftDiagonalIR - LEFT_WALL_THRES < 0) {
                error_p = leftDiagonalIR - LEFT_WALL_THRES;
            }
            else{
                error_p = rightDiagonalIR - leftDiagonalIR;
            }
            error_d = error_p - old_error_p;    
        }
        else if (has_left_wall) {
            error_p = 2 * (LEFT_WALL_THRES - leftDiagonalIR.readIR());
            error_d = error_p - old_error_p;
        }
        else if (has_right_wall) {
            error_p = 2 * (rightDiagonalIR.readIR() - RIGHT_WALL_THRES);
            error_d = error_p - old_error_p;
        }
        else if (!has_left_wall && !has_right_wall) {
            error_p = 0;
            error_d = 0;
        }
        total_error = P * error_p + D * (error_d - old_error_d);
        old_error_p = error_p;
        old_error_d = error_d;
        
        
        if(total_error < 7.5f){
            leftMotor -> speed(MOTOR_BASE_SPEED - total_error);
            rightMotor -> speed(MOTOR_BASE_SPEED + total_error);
        }
        else{
            leftMotor->speed(MOTOR_BASE_SPEED);
            rightMotor->speed(MOTOR_BASE_SPEED);
        }
    }
    
    void one_cell_turned(){
        leftEncoder.reset();
        rightEncoder.reset();
        while(leftEncoder.getEncoderDistance(1)<-46000 & leftEncoder.getEncoderDistance(1)<46000){
            //Do nothing
        }
    }
    
    // should use this method as the exit condition
    // in the pid_controller::navigate() method
    // resets the pid, encoders, etc.
    void one_cell_traversed() {
        leftEncoder.reset();
        rightEncoder.reset();
        old_error_p = old_error_d = total_error = 0.0f;
    }
    
    // TODO
    void turn (int dir) {
        // https://github.com/austinxiao-ucsd/Falcon-MicroMouse/blob/master/Micromouse_test/drive_control.h
        if (TURN_LEFT) { // Flip motor speed to do in place turning 
        }
        else { // TODO: ...
        }
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
    return curr_cell;
}

void DriveControl::turn_left() {
    // TODO: Add PID Control
    pid_controller::turn(TURN_LEFT);
}

int DriveControl::get_next_direction() {
    // TODO: Define the direction based on heuristic eval. 
    return 1;   
}

int DriveControl::get_next_state(int state) {
    // Simply drives the mouse for testing
    return DRIVE;
}

void DriveControl::getEncoder(){
    pc.printf("LeftEncoder Reading %d", leftEncoder.getEncoderDistance(1));
    pc.printf("RightEncoder Reading %d\n\r", rightEncoder.getEncoderDistance(0));
}

void DriveControl::turn_right() {
    // TODO: Add PID Control
    pid_controller::turn(TURN_RIGHT);
}

void DriveControl::turn_around() {
    // TODO: Add PID Control
    pid_controller::turn(TURN_AROUND);
}

void DriveControl::stop() {
    leftMotor->stop();
    rightMotor->stop(); 
}

void DriveControl::drive_forward() {
    pid_controller::navigate();
}


// TODO: Test top right ir sensor 
bool DriveControl::has_front_wall() {
    return rightFrontIR > FRONT_SENSOR_THRESHOLD;
}

bool DriveControl::has_left_wall() {
    return leftIR < SENSOR_THRESHOLD;
}

bool DriveControl::has_right_wall() {
    return rightIR < SENSOR_THRESHOLD;
}

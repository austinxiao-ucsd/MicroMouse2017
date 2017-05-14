#include "drivecontrol.h"
#include "Cell.h"
//#include "mbed.h"
#include "ir_sensor.h"
#include "left_motor.h"
#include "right_motor.h"
#include "pin_assignment.h"

IRSensor leftIR(PA_8, PC_5);
IRSensor rightIR(PB_0, PA_4);
// Bit to specify debugging mode
const bool DEBUG = false;
// Define states for debugging the mouse hardware
const int DRIVE = 0, TURN = 2, STOP = 4;
const int SENSOR_THRESHOLD = 12;
LeftMotor * leftMotor;
RightMotor * rightMotor;
Cell * curr_cell;
Serial pc(PA_9, PA_10);

float motor_speed;
//float LEFT_WALL_THRES = 0.86f, RIGHT_WALL_THRES = 0.86f;
float LEFT_WALL_THRES = 0.46f, RIGHT_WALL_THRES = 0.21f;
float SENSOR_ERROR_OFFSET = 0.0f;

float left_speed;
float right_speed;
float error_p = 0.0f, old_error_p = 0.0f, old_error_d = 0.0f, error_d = 0.0f;
float total_error = 0.0f;
float P = 18.0f, D = 3.0f;

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

/*
IRSensor rightDiagonalIR(PA_8, PA_5);
IRSensor rightFrontIR(PB_0, PA_6);
IRSensor leftFrontIR(PB_1, PA_7);
IRSensor leftDiagonalIR(PC_6, PC_4);
*/

void DriveControl::drive_one_forward() {
    if (DEBUG) { rightMotor->speed(15); leftMotor->speed(15);}
    else {
    //    pid_controller::start_pid();
    //    total_error = pid_controller::get_error();
        bool has_left_wall = leftDiagonalIR.readIR() > LEFT_WALL_THRES;
        bool has_right_wall = rightDiagonalIR.readIR() > RIGHT_WALL_THRES;
       // pc.printf("Left sensor: %f\n\r", leftDiagonalIR.readIR());//leftIR.readIR());
       // pc.printf("Right sensor: %f\n\r", rightDiagonalIR.readIR());//rightIR.readIR());
       // pc.printf("Different: %f\n\r", rightDiagonalIR.readIR() - leftDiagonalIR.readIR());
        
        
        old_error_d = error_d;
        if (has_left_wall && has_right_wall) {
//              pc.printf("Has both wall \r\n");
            float tmp_dist;
            if (rightDiagonalIR - RIGHT_WALL_THRES < 0) {
                tmp_dist = rightDiagonalIR - RIGHT_WALL_THRES;
            }
            else if (leftDiagonalIR - LEFT_WALL_THRES < 0) {
                tmp_dist = leftDiagonalIR - LEFT_WALL_THRES;
            }
            else{
                tmp_dist = rightDiagonalIR - leftDiagonalIR;
            }
            error_p = tmp_dist;
            //error_p = rightDiagonalIR - leftDiagonalIR - SENSOR_ERROR_OFFSET;
            error_d = error_p - old_error_p;    
        }
        else if (has_left_wall) {
//              pc.printf("Has right wall \r\n");
            error_p = 2 * (LEFT_WALL_THRES - leftDiagonalIR.readIR());
            error_d = error_p - old_error_p;
        }
        else if (has_right_wall) {
//              pc.printf("Has left wall \r\n");
            error_p = 2 * (rightDiagonalIR.readIR() - RIGHT_WALL_THRES);
            error_d = error_p - old_error_p;
        }
        else if (!has_left_wall && !has_right_wall) {
//            pc.printf("Not has wall \r\n");
            error_p = 0;
            error_d = 0;
        }
        
//        pc.printf("old error p %f\n\r", old_error_p * 100);
//        pc.printf("error p %f\n\r", error_p * 100);
//        pc.printf("error d %f\n\r", error_d * 100);
//        pc.printf("p %f\n\r", P * 100);
//        pc.printf("d %f\n\r", D * 100);
        total_error = P * error_p + D * (error_d - old_error_d);
        old_error_p = error_p;
        
        // if (DEBUG) { leftMotor->speed(0.15f); rightMotor->speed(0.85f); }
        
        //adjust to right
       
        //pc.printf("total error %f\n\r", total_error);
        
        if(total_error < 7.5f){
            leftMotor -> speed(15 - total_error);
            rightMotor -> speed(15 + total_error);
        }
        else{
            leftMotor->speed(7.5);
            rightMotor->speed(22.5);
        }
        
    }   
}


bool DriveControl::has_front_wall() {
 //   return rightFrontIR < SENSOR_THRESHOLD && leftFrontIR < SENSOR_THRESHOLD;
}

bool DriveControl::has_left_wall() {
    return leftIR < SENSOR_THRESHOLD;
}

bool DriveControl::has_right_wall() {
    return rightIR < SENSOR_THRESHOLD;
}

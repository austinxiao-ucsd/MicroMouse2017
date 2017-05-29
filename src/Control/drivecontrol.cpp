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

// Sensor offsets
//float FRONT_SENSOR_THRES = 7.0f, SENSOR_ERROR_OFFSET = 0.0f;
float FRONT_SENSOR_THRES = 2.2f, SENSOR_ERROR_OFFSET = 0.0f;
//float LEFT_WALL_THRES = 0.336f, RIGHT_WALL_THRES = 0.163f;
float LEFT_WALL_THRES = 0.336f, RIGHT_WALL_THRES = 0.163f;
float RIGHT_SIDE_WALL_THRES = 0.20f, LEFT_SIDE_WALL_THRES = 0.20f;
//float RIGHT_SIDE_WALL_THRES = 0.28f, LEFT_SIDE_WALL_THRES = 0.38f;

// Motor speed offsets
float left_speed, right_speed, motor_speed;
float MOTOR_BASE_SPEED = 20.0f; //12.0f;
float cool_down_offset = 0.0f;
//
//    bool right_front_wall = (rightFrontIR.readIR() * 1000) > 355.0f;//350.39f;
//    bool left_front_wall = (leftFrontIR.readIR() * 1000) > 315.0f;//310.25f;

float RIGHT_FRONT_THRES = 355.0f;
float LEFT_FRONT_THRES = 315.0f;

bool enter_right_wall_pid_debug = false;

// Encoder offsets
int ENCODER_TURN_UNIT = 16500;

namespace pid_controller { 
    // PID Constants
    float error_p = 0.0f, old_error_p = 0.0f, old_error_d = 0.0f, error_d = 0.0f;
    float total_error = 0.0f;
    float P = 18.0f, D = 20.0f;
    
    void navigate() {
        bool has_left_wall = leftDiagonalIR.readIR() > LEFT_WALL_THRES;
        bool has_right_wall = rightDiagonalIR.readIR() > RIGHT_WALL_THRES;

        if (has_left_wall && has_right_wall) {
            enter_right_wall_pid_debug = false;
            if (rightDiagonalIR - RIGHT_WALL_THRES < 0) {
                error_p = rightDiagonalIR - RIGHT_WALL_THRES;
            }
            else if (leftDiagonalIR - LEFT_WALL_THRES < 0) {
                error_p = LEFT_WALL_THRES - leftDiagonalIR;
            }
            else{
                error_p = rightDiagonalIR - leftDiagonalIR;
                enter_right_wall_pid_debug = true; 
            }
            error_d = error_p - old_error_p;  
             
        }
//        float RIGHT_SIDE_WALL_THRES = 0.59f, LEFT_SIDE_WALL_THRES = 0.38f;
        else if (has_left_wall) {
           // error_p = 4 * (LEFT_WALL_THRES - 0.50 * leftDiagonalIR.readIR());
           error_p = LEFT_WALL_THRES - leftDiagonalIR.readIR();
            //error_p = 2 * (LEFT_SIDE_WALL_THRES - leftIR.readIR());
            error_d = error_p - old_error_p;
            enter_right_wall_pid_debug = false;
        }
        else if (has_right_wall) {
            error_p = rightDiagonalIR.readIR() - RIGHT_WALL_THRES;
            //error_p = 2 * (RIGHT_SIDE_WALL_THRES - rightIR.readIR();
            error_d = error_p - old_error_p;
            enter_right_wall_pid_debug = false;
        }
        else if (!has_left_wall && !has_right_wall) {
            error_p = 0;
            error_d = 0;
            enter_right_wall_pid_debug = false;
        }
        total_error = P * error_p + D * (error_d - old_error_d);
        old_error_p = error_p;
        old_error_d = error_d;
        
        //MOTOR_BASE_SPEED -= cool_down_offset;
        if(total_error < 7.5f){
            leftMotor -> speed(MOTOR_BASE_SPEED - total_error);
            rightMotor -> speed(MOTOR_BASE_SPEED + total_error);
        }
        else{
            leftMotor->speed(MOTOR_BASE_SPEED);
            rightMotor->speed(MOTOR_BASE_SPEED);
        }
        
        
    }
    
    void clear_pid(){
        error_p = 0.0f, old_error_p = 0.0f, old_error_d = 0.0f, error_d = 0.0f;
        total_error = 0.0f;
    }
    
    void cool_down_speed() {
        if (cool_down_offset < 5.0f) {
            cool_down_offset += 2.0f;
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
    void turn (bool turn_right) {
        float MOTOR_TURN_SPEED = 14.0f;
        
        if (turn_right) {
            leftMotor -> speed(MOTOR_TURN_SPEED);
            rightMotor -> speed(-MOTOR_TURN_SPEED);
        }
        else {
            leftMotor -> speed(-MOTOR_TURN_SPEED);
            rightMotor -> speed(MOTOR_TURN_SPEED);
        }
    }
}

bool DriveControl::right_wall_pid_debug() {
    return enter_right_wall_pid_debug;
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

int DriveControl::get_next_direction() {
    // TODO: Define the direction based on heuristic eval. 
    return 1;   
}

void DriveControl::print_serial_ports(){
    pc.printf("LEFT Encoder Reading %d\n\r", leftEncoder.getEncoderDistance(1));
    pc.printf("RIGHT Encoder Reading %d\n\r", rightEncoder.getEncoderDistance(0));
    pc.printf("FRONT TOP RIGHT IRSensor %f\n\r", rightFrontIR.readIR() * 1000);
    pc.printf("FRONT TOP LEFT IRSensor %f\n\r", leftFrontIR.readIR() * 1000);
    pc.printf("LEFT Diagonal Sensor %f\n\r", leftDiagonalIR.readIR());
    pc.printf("RIGHT Diagonal Sensor %f\n\r", rightDiagonalIR.readIR());
    pc.printf("LEFT SIDE Sensor %f\n\r", leftIR.readIR());
    pc.printf("RIGHT SIDE Sensor %f\n\r", rightIR.readIR());
}

void DriveControl::turn_left() {
    // TODO: Add PID Control
    pid_controller::turn(false);
}

void DriveControl::set_wall_follower_sensor_thres(){
    //TODO
    RIGHT_FRONT_THRES = 300.0f;
    LEFT_FRONT_THRES = 250.0f;
}

void DriveControl::turn_right() {
    // TODO: Add PID Control
    pid_controller::turn(true);
}

void DriveControl::set_wall_follower_speed() {
    MOTOR_BASE_SPEED  = 25;
}

void DriveControl::turn_around() {
    // TODO: Add PID Control
    //pid_controller::turn(TURN_AROUND);
    pid_controller::turn(true);
}

void DriveControl::stop() {
    leftMotor->stop();
    rightMotor->stop(); 
}

void DriveControl::resetEncoders() {
    leftEncoder.resetEncoders();
    rightEncoder.resetEncoders();
}

void DriveControl::drive_forward() {
    pid_controller::navigate();
    
}

bool DriveControl::should_stop_drive_forward() {
    float SHOULD_STOP = 7.0f;
    return (rightFrontIR.readIR() * 1000) > SHOULD_STOP;
}

bool DriveControl::should_finish_turn_right() {
    int max = 
        (leftEncoder.getEncoderDistance(1) < rightEncoder.getEncoderDistance(0))
        ? rightEncoder.getEncoderDistance(0):leftEncoder.getEncoderDistance(1);
    return max < - ENCODER_TURN_UNIT;
}

bool DriveControl::should_finish_turn_left() {
    int min_two = 
        (leftEncoder.getEncoderDistance(1) > rightEncoder.getEncoderDistance(0))
        ? rightEncoder.getEncoderDistance(0):leftEncoder.getEncoderDistance(1);
    return min_two > ENCODER_TURN_UNIT;
}

bool DriveControl::should_finish_drive_forward() {
    int max_two = 
        (- leftEncoder.getEncoderDistance(1) < rightEncoder.getEncoderDistance(0))
        ? rightEncoder.getEncoderDistance(0):- leftEncoder.getEncoderDistance(1);
    return max_two > 36000;
}

bool DriveControl::has_front_wall() {
//    float RIGHT_FRONT_THRES = 355.0f;
//float LEFT_FRONT_THRES = 315.0f;
    bool right_front_wall = (rightFrontIR.readIR() * 1000) > RIGHT_FRONT_THRES;//350.39f;
    bool left_front_wall = (leftFrontIR.readIR() * 1000) > LEFT_FRONT_THRES;//310.25f;
    return right_front_wall || left_front_wall;
}

bool DriveControl::has_left_wall() {
    return leftIR.readIR() > LEFT_SIDE_WALL_THRES;
}

bool DriveControl::has_right_wall() {
    return rightIR.readIR() > RIGHT_SIDE_WALL_THRES;
}

void DriveControl::clear_pid() {
    pid_controller::clear_pid();
}

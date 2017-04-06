#include "mbed.h"
#include "ir_sensor.h"

const int FRONT_THRESHOLD = 12;

/*
 * front_wall_dist
 * Parameters: None
 * Returns: float, distance in cm from FRONT WALL
 */
float front_wall_dist()
{
    float right = rightFrontIR;
    
    return rightFrontIR;
}

/*
 * left_wall_dist
 * Parameters: None
 * Returns: float, distance in cm from LEFT WALL
 */
float left_wall_dist()
{
    return leftIR;
}

/*
 * right_wall_dist
 * Parameters: None
 * Returns: float, distance in cm from RIGHT WALL
 */
float right_wall_dist()
{
    return rightIR;
}

bool has_front_wall() {
    return rightFrontIR < FRONT_THRESHOLD && leftFrontIR < FRONT_THRESHOLD;
}
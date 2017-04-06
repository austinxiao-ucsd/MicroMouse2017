/**
    PIDController.h
    Purpose: Instantiate an PID Controller Object to adjust
    mouse position based on sensor-read values. Implemented
    the PID control mechanisms to adjust motor offsets.

    @author Hongda Xiao
    @version 1.0 12/24/2016
*/

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <mbed.h>

class PIDController {
  private:
    float i_term = 0;
    // Replace with Arduino Timer function to calculate elapsed time.
    //elapsedMicros elapsed_time;
    float last_value = NAN;
    float kp, ki, kd;
    float i_lower_bound, i_upper_bound;

  public:
    /**
      Constructs an PID Controller object
    */
    PIDController(float tempKP, float tempKI, float tempKD, float temp_i_upper_bound = 10000,
                  float temp_i_lower_bound = 0);

    /** 
      Calculates the target speed to offset the PWM cycle of the motor

      @param current_value: value that is the current position of the mouse
             target_value: the target position value for the mouse
      @return the offset to add to the motor PWM signal
    */
    float Calculate(float current_value, float target_value);
};

#endif
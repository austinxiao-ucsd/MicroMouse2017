#include "PIDController.h"

#include <mbed.h>

PIDController::PIDController(float curr_kp, float curr_ki, float curr_kd, float temp_i_upper_bound,
                             float temp_i_lower_bound) {
  kp = curr_kp;
  ki = curr_ki;
  kd = curr_kd;
  
  if (temp_i_lower_bound == 0) {
    temp_i_lower_bound = -temp_i_upper_bound;
  }

  i_lower_bound = temp_i_lower_bound;
  i_upper_bound = temp_i_upper_bound;
}

float PIDController::Calculate(float current_value, float target_value) {
  float error = current_value - target_value;

  i_term += ki * error * elapsed_time;

  // setting a constrain on i_term boundary
  if (i_term < i_lower_bound) {
    i_term = i_lower_bound;
  }
  if (i_term > i_upper_bound) {
    i_term = i_upper_bound;
  }

  if (isnan(last_value)) {
    last_value = current_value;
  }

  float output = -kp * error - i_term + kd * (last_value - current_value) / elapsed_time;
  last_value = current_value;

  elapsed_time = 0;

  return output;
}

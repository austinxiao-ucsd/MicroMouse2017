#include "drivecontrol.h"
#include "Cell.h"

const int POS_TURN_CONST = 0.5f, NEG_TURN_CONST = -0.5f;

Cell * curr_cell;

DriveControl::DriveControl (int start_x, int start_y) {
    curr_cell = new Cell (start_x, start_y);
}

// Defines the next cell to traverse.
Cell * next_cell() {
    Cell * cell;
    // TODO: Check for cell based on updated distances
    return cell;
}

void DriveControl::turn_left() {
    leftMotor = NEG_TURN_CONST;
    rightMotor = POS_TURN_CONST;
}
    
// Turn the mouse to the right dir
void DriveControl::turn_right() {
    leftMotor = POS_TURN_CONST;
    rightMotor = NEG_TURN_CONST;
}

void DriveControl::drive_one_forward() {
}

  
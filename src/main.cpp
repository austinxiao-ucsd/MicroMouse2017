#include "mbed.h"
#include "drivecontrol.h"
#include "pin_assignment.h"

AnalogIn battery(PA_3);
Serial pc(PA_9, PA_10);

// Define states for debugging the mouse hardware
static const int DRIVE = 1, TURN = 2, DEBUG = 3, STOP = 4;
// Direction of which to turn
static const int LEFT = 0, RIGHT = 1;
// Start and End Pos
static const int START_POS = 0, END_POS = 0;
// Terminating condition for the main control loop
bool hasFoundCenter = false;

// Battery Consumption Indicator
void setup() {
    pc.baud(9600);
    if (battery.read() < 0.73f){
    }  
}

// Performs the basic drive control of the mouse
int main() {
    DriveControl * driver = new DriveControl(START_POS, END_POS);
    int state = DRIVE;
    while(!hasFoundCenter) {
        switch (state) {
            case DRIVE:
                driver->drive_one_forward();
            case TURN:
                if (driver->get_next_direction() == LEFT) {
                    driver->turn_left();
                }
                else if (driver->get_next_direction() == RIGHT) {
                    driver->turn_right();    
                }
            case STOP:
                driver->stop();
            case DEBUG:
                // TODO
            default:
                // Error Condition. Flash all lights.
                break;  
        }
    }
}

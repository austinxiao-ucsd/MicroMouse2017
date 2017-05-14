#include "drivecontrol.h"
#include "pin_assignment.h"
#include "io_modules.h"

// Define states for debugging the mouse hardware
// const int DRIVE = 1, TURN = 2, DEBUG = 3, STOP = 4;
// Direction of which to turn
// const int LEFT = 0, RIGHT = 1;
// Start and End Pos
const int START_POS = 0, END_POS = 0;

// Terminating condition for the main control loop
bool hasFoundCenter = false;

// Battery Consumption Indicator
void setup() {
    pc.baud(9600);
    // using the serial functions will have an impact on timing.
    // serial.printf("voltage value is: %3.3f%%\r\n", battery.read()*100.0f);
    // serial.printf("normalized: 0x%04X \r\n", battery.read_u16());
    if (battery.read() < 0.67f){
        // flash led
        led_1 = 1;
        led_2 = 1;
        led_3 = 1;
        led_4 = 1;
    }  
}

// Performs the basic drive control of the mouse
int main() {
    DriveControl * driver = new DriveControl (START_POS, END_POS);
    while(1) {
        setup();
        led_1 = 1;
        driver->drive_one_forward();
        wait(0.5);
        driver->stop();
        wait(10);
    }
}
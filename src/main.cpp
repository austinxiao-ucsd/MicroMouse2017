#include "drivecontrol.h"
#include "io_modules.h"
#include "mbed.h"
#include "maze_solver.h"

//// PIN ASSIGNMENTS
AnalogIn battery(PA_3);
DigitalOut led_1(PB_12);
DigitalOut led_2(PB_13);
DigitalOut led_3(PB_14);
DigitalOut led_4(PB_15);
Serial serial (PA_9, PA_10);

// ALGORITHM SWITCH
DigitalIn alg_pin (PC_10);

// CONTROL CONSTANTS
const unsigned char  STRAIGHT = 0, LEFT = 1, RIGHT = 2, UTURN = 3;
const int START_POS = 0, END_POS = 0;
const int CONTROL = 1;
unsigned char state;

void check_battery () {
    // pc.baud(9600);
    // using the serial functions will have an impact on timing.
    // serial.printf("voltage value is: %3.3f%%\r\n", battery.read()*100.0f);
    // serial.printf("normalized: 0x%04X \r\n", battery.read_u16());
    if (battery.read() < 0.70f){
        // flash led
        led_1 = 1;
        led_2 = 1;
        led_3 = 1;
        led_4 = 1;
    }
}

void flash_led (int _led_1, int _led_2, int _led_3, int _led_4) {
    led_1 = _led_1;
    led_2 = _led_2;
    led_3 = _led_3;
    led_4 = _led_4;
}

void run_flood_fill_algorithm() {
    DriveControl * driver = new DriveControl (START_POS, END_POS);
    Mouse * my_mouse = new Mouse(driver);
    driver->resetEncoders();
    int count = 0;
    bool finished_traverse_one_cell = true;
    wait(1);
    
    while(CONTROL) {
        check_battery();
        wait_ms(1);
        if (finished_traverse_one_cell == true) {
            if (my_mouse->center_found()) {
                flash_led(1,1,1,1);
            }
            state = my_mouse->solve_maze();
            wait(0.5);
            if(state == RIGHT){
                wait(0.25);
                driver->resetEncoders();
            }
            else if(state == LEFT){
                wait(0.25);
                driver->resetEncoders();
            }
            else if(state == UTURN){
                wait(0.25);
                driver->resetEncoders();
                count = 0;
            }else{
                state = STRAIGHT;
            }
            finished_traverse_one_cell = false;
        }
        
        if (state == STRAIGHT) {
            if (!driver->should_finish_drive_forward() && !driver-> has_front_wall()) {
                driver->drive_forward();
               
            }
            else {
                driver->stop();
                wait(0.25);
                driver->resetEncoders();
                finished_traverse_one_cell = true;
                continue;
            }
        }
        if (state == RIGHT) {
            if (!driver->should_finish_turn_right()) {
                driver->turn_right();
            }
            else {
                driver->stop();
                state = STRAIGHT;
                wait(0.25);
                driver->resetEncoders();
                driver->clear_pid();
                continue;
            }
        }
        if (state == LEFT) {
            if (!driver->should_finish_turn_left()) {
                driver->turn_left();
            }
            else {
                driver->stop();
                state = STRAIGHT;
                wait(0.25);
                driver->resetEncoders();
                driver->clear_pid();
                continue;
            }
        }
        
        if (state == UTURN){
            if (!driver->should_finish_turn_left()) {
                driver->turn_left();
            }
            else {
                driver->stop();
                driver->resetEncoders();
                wait(0.25);
                if(count == 1) {
                    state = STRAIGHT;
                }
                count ++;//
                continue;
            }
        }
    }
}

int main() {
    if (alg_pin) {
        flash_led(1,0,1,0);
        wait(2);
        run_flood_fill_algorithm();
    }   
}
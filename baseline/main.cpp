#include "mbed.h"
#include "pin_assignment.h"

// Battery Consumption Indicator
void setup() {
    pc.baud(9600);
    if (battery.read() < 0.73f){
    //    ledRed = 1;
    }  
}

int main() {
    while(1) {
        
    }
}

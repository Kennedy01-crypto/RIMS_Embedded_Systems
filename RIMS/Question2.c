#include "RIMS.h"

volatile unsigned char TimerFlag = 0;
unsigned char t1, t2, t3;

void TimerISR() {
    TimerFlag = 1;
}

enum States { Init, Average } state;

void Tick() {
    switch(state) {
        case Init:
            t1 = t2 = t3 = A; // Initialize all readings to the first input
            B = A;
            state = Average;
            break;

        case Average:
            t3 = t2;          // Shift readings
            t2 = t1;
            t1 = A;          // Take new reading
            B = (t1 + t2 + t3) / 3; // Calculate average
            break;

        default:
            state = Init;
            break;
    }
}

void main() {
    TimerSet(3000); // 3 seconds sampling period
    TimerOn();
    B = 0;
    state = Init;

    while(1) {
        Tick();
        while (!TimerFlag); // Wait for the timer
        TimerFlag = 0;
    }
}

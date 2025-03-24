#include "RIMS.h"

volatile unsigned char TimerFlag = 0; // Timer flag to synchronize events
unsigned short delay = 0;            // Variable to track the delay
unsigned short cnt = 0;              // Counter to measure reaction time

void TimerISR() {
    TimerFlag = 1; // Triggered every timer period
}

enum States { WaitStart, Delay, Signal, Measure, Show } state;

void Tick() {
    switch(state) {
        case WaitStart: // Wait for the start signal (A0 HIGH)
            B = 0; 
            cnt = 0; 
            delay = 0; 
            if (A0) {
                state = Delay;
            }
            break;

        case Delay: // Introduce a 3-second delay after start signal
            delay++;
            if (delay >= 300) { // 300 * 10ms = 3 seconds
                B0 = 1; // Turn LED ON (stimulus)
                cnt = 0; // Reset counter
                state = Measure;
            }
            break;

        case Measure: // Measure reaction time (until button press A1)
            cnt++;
            if (A1) { // Button press detected
                state = Show;
            }
            break;

        case Show: // Output reaction time and reset LED
            B = cnt; // Reaction time output (in x10 ms units)
            B0 = 0;  // Turn LED OFF
            if (!A0) {
                state = WaitStart; // Wait for another trial
            }
            break;

        default:
            state = WaitStart;
            break;
    }
}

void main() {
    TimerSet(10); // Timer set for 10ms intervals
    TimerOn();
    state = WaitStart; // Initialize state
    B = 0;

    while(1) {
        Tick(); // Call the state machine function
        while (!TimerFlag); // Wait for timer tick
        TimerFlag = 0; // Reset timer flag
    }
}

#include "RIMS.h" 
volatile unsigned char TimerFlag = 0; 
void TimerISR() { 
    TimerFlag = 1; 
} 

enum States { L0, L1, L2 } state; 

void Tick() { 
    switch(state) { 
        case L0: B = 0x01; state = L1; break; 
        case L1: B = 0x02; state = L2; break; 
        case L2: B = 0x04; state = L0; break; 
    } 
} 
void main() { 
    TimerSet(1000); 
    TimerOn(); 
    B = 0; 
    state = L0;     
    
    while(1) { 
        Tick(); 
        while (!TimerFlag); 
        TimerFlag = 0; 
    } 
}

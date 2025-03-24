#include <avr/io.h>
#include <util/delay.h>

void main(void) {
    // Set B3..B0 as output
    DDRB = 0x0F;

    // Initialize the counter
    uint8_t counter = 0;

    while (1) {
        // Display the counter value on B3..B0
        PORTB = (PORTB & 0xF0) | (counter & 0x0F);

        // Increment the counter
        counter++;

        // Reset the counter after reaching 15
        if (counter > 15) {
            counter = 0;
        }

        // Wait for 500ms
        _delay_ms(500);
    }
}

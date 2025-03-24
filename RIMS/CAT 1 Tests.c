#include <rims.h>

void main() {
    unsigned char Park_Space;
    unsigned char i; // Declare `i` at the beginning
    
    while (1) {
        Park_Space = 0;
        for (i = 0; i < 8; i++) {
            if (!(A & (1 << i))) Park_Space++; // Count empty Park_Space
        }
        B = (Park_Space << 5) | (Park_Space == 0 ? 1 : 0); // Display available Park_Space and full indicator
    }
}

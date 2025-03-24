#include"RIMS.h"
 void main()
 {
    
        unsigned char availableSpaces = 0;
    while(1){
        // Check if both handicapped spaces are full (A7 and A6 are both 1)
        if ((A & 0xC0) == 0xC0) {
            B0 = 1; // Set B0 to 1 if both are full
        } else {
            B0 = 0; // Set B0 to 0 otherwise
        }

        // Count the number of available non-handicapped spaces (A5..A0)
        if (!(A & 0x20)) availableSpaces++; // A5
        if (!(A & 0x10)) availableSpaces++; // A4
        if (!(A & 0x08)) availableSpaces++; // A3
        if (!(A & 0x04)) availableSpaces++; // A2
        if (!(A & 0x02)) availableSpaces++; // A1
        if (!(A & 0x01)) availableSpaces++; // A0

        // Set B7..B5 to the number of available non-handicapped spaces
        B = (availableSpaces << 5) | (B & 0x1F); // Preserve lower bits (B4..B0) and update upper bits (B7..B5)
    }
 }
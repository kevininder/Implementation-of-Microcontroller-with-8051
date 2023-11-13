/* Display number 1 to 10 on a 7-segment display with 8051 */

#include <8052.h>

void main() {
    unsigned char number[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};

    for (int i = 0; i < 10; i++) {
        P2 = number[i];
        for (int j = 0; j < 40000; j++);
    }
    
    while (1);
}
/* Write an 8051 C program to monitor bit P1.5. If it is low, turn on LED; otherwise, turn off it.
   Connect LED to P2.0.
*/

#include <8052.h>

sbit SW = P1^5;
sbit LED = P2^0;

void main() {
    while (1) {
        !SW ? LED = 1 : LED = 0;
    }
}
/* Write an 8051 C program to toggle only the bit P2.4 continuously without disturbing the rest of the bits of P2. */

#include <8052.h>

sbit PIN = P2^4;

void msDelay(int s) {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < 1275; j++);
    }
}

void main() {
    while (1) {
        PIN = 0;
        msDelay(250);
        PIN = 1;
        msDelay(250);
    }
}
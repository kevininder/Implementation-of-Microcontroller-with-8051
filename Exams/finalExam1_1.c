/* Write an 8051 C program to toggle only the pin P1.5 continuously every 50ms.
   Use Timer0, mode1 (16 bit) to create the delay.
*/

#include <8052.h>

sbit LED = P1^5;

void delay50ms();

void main() {
    while (1) {
        LED = 0;;
        delay50ms();
        LED = 1;
        delay50ms();
    } 
}

void delay50ms() {
    TMOD = 0x01;
    TH0 = 0x4B;
    TL0 = 0xFE;
    TR0 = 1;
    while (!TF0);
    TF0 = 0;
    TR0 = 0;
}
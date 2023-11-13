/* Introduction to interrupts(ISR) P1.
   Write a C program that continuously gets a single bit of data from P1.7 and sends it to P1.0,
   while simultaneously creating a square wave of 200 μs period on pin P2.5.
   Use Timer0 to create the square wave. Assume that XTAL = 11.0592 MHz.
   
   EXT intr0: interrupt 0
   timer0: interrupt 1
   EXT intr1: interrupt 2
   timer1: interrupt 3
   serial intr: interrupt 4
*/

#include <8052.h>

sbit IN = P1^7;
sbit OUT = P1^0;
sbit WAVE = P2^5;

void timer0INTR() interrupt 1{
    WAVE = ~WAVE;
    TF0 = 0;
}

void main() {
    TMOD = 0x02;
    TH0 = 0xA4;
    TL0 = 0xA4;
    IE = 0x82; // enable timer0 interrupt
    IR0 = 1;

    while (1) {
        OUT = IN;
    }
}
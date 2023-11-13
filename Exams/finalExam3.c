/* Write a C program via interrupts to do the following tasks:
   (a) Receive data serially and send it to P1 in serial interrupt context.
   (b) Get a single bit of data from P2.7 and send it to P2.0 in the main program.
   Assume XTAL = 11.0592 Mhz and baud rate at 9600.
*/

#include <8052.h>

sbit IN = P2^7;
sbit OUT = P2^0;

void serialIntr() interrupt 4{
    P1 = SBUF;
    RI = 0;
}

void main() {
    TMOD = 0x20;
    TH1 = 0xFD;
    SCON = 0x50;
    IE = 0x90;
    TR1 = 1;

    while (1) {
        OUT = IN;
    }
}
/* Design a C program for counter0 in mode1 (16 bit) to count the pulses,
   and display the state of TH0 and TL0 registers on LCD.
   Note. You can use any pins you like to meet the requirements.
   Hint. Some pin(s) may not be available.
*/

#include <8052.h>

sbit RS = P2^0;
sbit EN = P2^1;
sfr DATA = 0x90;

void lcdInit();
void lcdCmd(unsigned char d);
void lcdData(unsigned char d);
void lcdString(unsigned char *str);
void hexToASCII(unsigned char value);
void msDelay(int s);

void main() {
    lcdInit();
    lcdString("  TL0=          ");
    lcdCmd(0xC0);
    lcdString("  TH0=          ");

    while (1) {
        TMOD = 0x05;
        TL0 = 0x00;
        TH0 = 0x00;
        TR0 = 1;

        do {
            lcdCmd(0x86);
            hexToASCII(TL0);
            lcdCmd(0xC6);
            hexToASCII(TH0);
        } while (!TF0);

        TR0 = 0;
        TF0 = 0;
    } 
}

void lcdInit() {
    lcdCmd(0x38);
    lcdCmd(0x0C);
    lcdCmd(0x01);
    lcdCmd(0x80);
}

void lcdCmd(unsigned char d) {
    RS = 0;
    DATA = d;
    EN = 1;
    msDelay(5);
    EN = 0;
    msDelay(5);
}

void lcdData(unsigned char d) {
    RS = 1;
    DATA = d;
    EN = 1;
    msDelay(5);
    EN = 0;
    msDelay(5);
}

void lcdString(unsigned char *str) {
    while (*str) {
        lcdData(*str++);
    }
}

void hexToASCII(unsigned char value) {
    unsigned char d1, d2, d3;

    d1 = value / 10 / 10;
    d2 = value / 10 % 10;
    d3 = value % 10;
    lcdString(d1 + 0x30);
    lcdString(d2 + 0x30);
    lcdString(d3 + 0x30);
}

void msDelay(int s) {
    for (int i = 0; i < s; i++);
}
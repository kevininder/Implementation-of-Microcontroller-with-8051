/* Write a C program to receive bytes of data in a serial manner via serial port and put them on LCD.
   Set the baud rate at 9600, 8-bit data, 1 start bit and 1 stop bit.
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
void msDelay(int s);

void main() {
    int i = 0;
    TMOD = 0x20;
    TH1 = 0xFD;
    SCON = 0x50;
    TR1 = 1;

    lcdInit();

    while (1) {
        while (!RI);
        i++;
        if (i == 17) lcdCmd(0xC0);
        if (i == 33) {
            i = 0;
            lcdCmd(0x80);
        }
        lcdData(SBUF);
        RI = 0;
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

void msDelay(int s) {
    for (int i = 0; i < s; i++);
}
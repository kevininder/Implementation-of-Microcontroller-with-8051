/* Follow the previous question, this time, write an 8051 C program to monitor bit P2.5. If it is low, turn ON LED; otherwise, turn OFF it.
   Connect LED across P2.6. Send current LED status via the serial port and display it on LCD.
*/

#include <8052.h>

sbit RS = P2^0;
sbit EN = P2^1;
sbit SW = P2^5;
sbit LED = P2^6;
sfr DATA = 0x90;

void lcdInit();
void lcdCmd(unsigned char d);
void lcdData(unsigned char d);
void lcdString(unsigned char *str);
void serialData(unsigned char d);
void serialString(unsigned char *str);
void msDelay(int s);

void main() {
    LED = 0;
    TMOD = 0x20;
    TH1 = 0xFD;
    SCON = 0x50;
    TR1 = 1;

    lcdInit();
    lcdString("  LED STATUS:   ");

    while (1) {
        if (!SW) {
            LED = 1;
            lcdCmd(0xC0);
            lcdString("     LED ON     ");
            serialString("     LED ON     ");
            serialData(0x0D);
        }
        else {
            LED = 0;
            lcdCmd(0xC0);
            lcdString("    LED OFF     ");
            serialString("    LED OFF     ");
            serialData(0x0D);
        }
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

void serialData(unsigned char d) {
    SBUF = d;
    while (!TI);
    TI = 0;
}

void serialString(unsigned char *str) {
    while (*str) {
        serialSend(*str++);
    }
}

void msDelay(int s) {
    for (int i = 0; i < s; i++);
}
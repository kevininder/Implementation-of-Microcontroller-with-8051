/* MCP3204 ADC and a temperature sensor interfacing with 8051 via SPI */

#include <8052.h>

sbit RS = P2^0;
sbit EN = P2^1;
sbit CLK = P3^0;
sbit DIN = P3^1;
sbit DOUT = P3^2;
sbit CS = P3^3;
sfr DATA = 0x90;

void lcdInit();
void lcdCmd(unsigned char d);
void lcdData(unsigned char d);
void lcdString(unsigned char *str);
void hexToASCII(unsigned char value);
unsigned int SPI();
void msDelay(int s);

void main() {
    lcdInit();
    lcdString(" Temperature:   ");

    while (1) {
        lcdCmd(0xC0);
        hexToASCII(SPI() / 8.5 + 1);
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

unsigned int SPI() {
    unsigned int temp = 0;

    CS = 0; // chip select
    CLK = 0; DIN = 1; CLK = 1; // start
    CLK = 0; DIN = 1; CLK = 1; // single ended
    
    // CH0
    CLK = 0; DIN = 0; CLK = 1; // D2
    CLK = 0; DIN = 0; CLK = 1; // D1
    CLK = 0; DIN = 0; CLK = 1; // D0

    CLK = 0; DIN = 1; CLK = 1; // t sample
    CLK = 0; DIN = 1; CLK = 1; // null bit

    for (int i = 11; i >= 0; i--) {
        CLK = 0;
        if (DOUT) temp |= (1<<i);
        CLK = 1;
    }
    
    CS = 1;

    return temp;
}

void msDelay(int s) {
    for (int i = 0; i < s; i++);
}
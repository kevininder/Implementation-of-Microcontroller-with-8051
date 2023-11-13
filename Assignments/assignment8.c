/* LCD, ADC0804 and a temperature sensor interfacing with 8051.
   LCD 16x2 pin diagram: https://www.electronicsforu.com/technology-trends/learn-electronics/16x2-lcd-pinout-diagram
   ADC0804 pin diagram: https://components101.com/ics/adc0804-pinout-datasheet
*/

#include <8052.h>

sbit RS = P2^0; // 0: command register, 1: data register
sbit EN = P2^1;
sbit RD = P2^2;
sbit WR = P2^3;
sbit INTR = P2^4;
sfr ADC = 0x90; // Port1
sfr DATA = 0xB0; // Port3

void lcdInit();
void lcdCmd(unsigned char d);
void lcdData(unsigned char d);
void lcdString(unsigned char *str);
void hexToASCII(unsigned char value);
void msDelay(int s);

void main() {
    lcdInit();
    lcdCmd(0xC0);
    lcdString("Temperature:    ");

    while (1) {
        RD = 1;
        WR = 0;
        msDelay(100);
        WR = 1;
        while (INTR);
        msDelay(100);
        RD = 0;
        lcdCmd(0xCC);
        hexToASCII(ADC * 2);
        INTR = 1;
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
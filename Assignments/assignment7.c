/* LCD and keypad interfacing with 8051.
   LCD 16x2 pin diagram: https://www.electronicsforu.com/technology-trends/learn-electronics/16x2-lcd-pinout-diagram
*/

#include <8052.h>

sbit RS = P2^0; // 0: command register, 1: data register
sbit EN = P2^1;
sbit R1 = P1^0;
sbit R2 = P1^1;
sbit R3 = P1^2;
sbit R4 = P1^3;
sbit C1 = P1^4;
sbit C2 = P1^5;
sbit C3 = P1^6;
sfr DATA = 0xB0; // Port3

void lcdInit();
void lcdCmd(unsigned char d);
void lcdData(unsigned char d);
void lcdString(unsigned char *str);
void setColumns();
void setRows();
void msDelay(int s);

void main() {
    lcdInit();
    lcdString("       Hi!      ");
    lcdCmd(0xC0);
    lcdString("My name is Kevin");
    msDelay(65000);
    lcdCmd(0x01);
    lcdCmd(0x80);
    lcdString("     I love     ");
    lcdCmd(0xC0);
    lcdString("embedded systems");
    msDelay(65000);
    lcdCmd(0x01);
    lcdCmd(0x80);
    lcdString(" Press any key: ");
    lcdCmd(0xC0);

    while (1) {
        msDelay(65000);
        setColumns();

        if (!C1) {
            setRows();

            if (!R1) lcdString('1');
            if (!R2) lcdString('4');
            if (!R3) lcdString('7');
            if (!R4) lcdString('*');
        }
        else if (!C2) {
            setRows();

            if (!R1) lcdString('2');
            if (!R2) lcdString('5');
            if (!R3) lcdString('8');
            if (!R4) lcdString('0');
        }
        else if (!C3) {
            setRows();

            if (!R1) lcdString('3');
            if (!R2) lcdString('6');
            if (!R3) lcdString('9');
            if (!R4) lcdString('#');
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

void setColumns() {
    C1 = C2 = C3 = 1;
    R1 = R2 = R3 = R4 = 0;
}

void setRows() {
    R1 = R2 = R3 = R4 = 1;
    C1 = C2 = C3 = 0;
}

void msDelay(int s) {
    for (int i = 0; i < s; i++);
}
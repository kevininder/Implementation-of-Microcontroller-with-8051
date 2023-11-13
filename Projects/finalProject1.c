/* EEPROM 24C04 interfacing with 8051 via I2C */

#include <8052.h>

sbit RS = P2^0;
sbit EN = P2^1;
sbit SCL = P3^0;
sbit SDA = P3^1;
sfr DATA = 0x90;

void lcdInit();
void lcdCmd(unsigned char d);
void lcdData(unsigned char d);
void lcdString(unsigned char *str);
void I2CStart();
void I2CStop();
unsigned char I2CRead();
void I2CWrite(unsigned char data);
void msDelay(int s);

void main() {
    unsigned char data;

    lcdInit();
    lcdString("    I2C R/W     ");

    // Sending data to a slave device
    I2CStart();
    I2CWrite(0xA0);
    I2CWrite(0x00);
    I2CWrite('A');        
    I2CStop();

    msDelay(500);

    // Reading data from a slave device
    I2CStart();
    I2CWrite(0xA0);
    I2CWrite(0x00);
    I2CStart();
    I2CWrite(0xA1);
    data = I2CRead();
    I2CStop();

    lcdCmd(0xC0);
    lcdData(data);

    while (1);
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

void I2CStart() {
    SCL = SDA = 1;
    msDelay(5);
    SDA = 0;
    msDelay(5);
    SCL = 0;
}

void I2CStop() {
    SCL = SDA = 0;
    msDelay(5);
    SCL = 1;
    msDelay(5);
    SDA = 1;
}

unsigned char I2CRead() {
    unsigned char data = 0;
    bit b;

    for (int i = 0; i < 8; i++) {
        SCL = 1;
        b = SDA;
        msDelay(5);
        data = (data<<1);
        data |= b;
        SCL = 0;
    }
    
    SCL = SDA = 1;
    msDelay(5);
    SCL = 0;

    return data;
}

void I2CWrite(unsigned char data) {
    for (int i = 0; i < 8; i++) {
        SCL = 1;
        SDA = (data & 0x80) ? 1 : 0;
        msDelay(5);
        data = (data<<1);
        SCL = 0;
    }

    SCL = SDA = 1;
    msDelay(5);
    while (SDA);
    SCL = 0;
}

void msDelay(int s) {
    for (int i = 0; i < s; i++);
}
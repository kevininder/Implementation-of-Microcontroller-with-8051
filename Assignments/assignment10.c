/* Introduction to serial communication */

#include <8052.h>

void main() {
    TMOD = 0x20; // timer1 mode2
    TH1 = 0xFD; // 9600 baud rate
    SCON = 0x50; // 8bit data 1 start bit and 1 stop bit
    TR1 = 1;

    while (1) {
        // TX
        SBUF = 'A';
        while (!TI);
        TI = 0;

        // RX
        while (!RI);
        P1 = SBUF;
        RI = 0;
    }
}
/* Implementation of timer and counter */

#include <8052.h>

// timer0 mode0 timer1 mode0
void main() {
    TMOD = 0x00;
    TH0 = 0x00;
    TL0 = 0x00;
    TR0 = 1;
    while (!TF0);
    TR0 = 0;
    TF0 = 0;
}

// timer0 mode1 timer1 mode0
void main() {
    TMOD = 0x01; 
    TH0 = 0xEE; // 5ms in total
    TL0 = 0x00;
    TR0 = 1;
    while (!TF0);
    TR0 = 0;
    TF0 = 0;
}

// timer0 mode2 timer1 mode0
void main() {
    TMOD = 0x02;
    TH0 = 0x10;
    TL0 = 0x00;
    TR0 = 1;
    while (!TF0);
    TR0 = 0;
    TF0 = 0;
}

// timer0 mode3 timer1 mode0
void main() {
    TMOD = 0x03;
    TH0 = 0x10;
    TL0 = 0x00;
    TR1 = 1;
    while (!TF0);
    TR1 = 0;
    TF1 = 0;
}

// counter0 mode1 counter1 mode1
void main() {
    TMOD = 0x55;
    TH1 = 0x00;
    TL1 = 0x00;
    TR1 = 1;
    while (!TF1);
    TR1 = 0;
    TF1 = 0;
}
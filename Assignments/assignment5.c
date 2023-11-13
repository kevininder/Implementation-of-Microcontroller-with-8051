/* 8051 with L293D to control two motors/robot moves */

#include <8052.h>

void main() {
    unsigned char direction[] = {0x05, 0x00, 0x0A, 0x00, 0x09, 0x00, 0x06, 0x00};

    while (1) {
        for (int i = 0; i < 8; i++) {
            P2 = direction[i];
            for (int i = 0; i < 40000; i++);
        }
    }
}
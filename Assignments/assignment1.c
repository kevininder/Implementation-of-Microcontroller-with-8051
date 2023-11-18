#include <8052.h>

void main() {
    while (1) {
        P1 = 0x00;
        for (int i = 0; i < 50000; i++);
        P1 = 0xFF;
        for (int i = 0; i < 50000; i++);
    }
}

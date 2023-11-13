/* Control a bulb with 8051, a relay and a switch */

#include <8052.h>

sbit SW = P3^0;
sbit RELAY = P2^0;

void main() {
    while (1) {
        !SW ? RELAY = 1 : RELAY = 0;
    }
}
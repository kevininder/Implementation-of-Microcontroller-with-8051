/* Introduction to interrupts P2. 
   Assume that the INT1 pin is connected to a switch that is normally high.
   Whenever it goes low, it should turn on a LED. The LED is connected to P1.3.
   Note to self, for edge triggering, initialize ITX and IEX to 1 in the main function.
*/

// Level triggering
#include <8052.h>

sbit LED = P1^3;

void externalIntr1() interrupt 2{
    LED = 1;
}

void main() {
    LED = 0;
    IE = 0x84;
    while (1);
}
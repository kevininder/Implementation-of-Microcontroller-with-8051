/* A door sensor is connected to the P1.1 pin, and a buzzer is connected to P1.7.
   Write an 8051 C program to monitor the door sensor, and when it opens, sound the buzzer.
   You can sound the buzzer by sending a square wave of a few hundred Hz.
*/

#include <8052.h>

sbit DOOR = P1^1;
sbit BUZZER = P1^7;

void msDelay(int s) {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < 1275; j++);
    }
}

void main() {
    while (1) {
        if (DOOR) {
            BUZZER = 0;
            msDelay(25);
            BUZZER = 1;
            msDelay(25);
        }
    }
}
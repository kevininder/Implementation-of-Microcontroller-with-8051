/* A switch is connected to pin P1.2. Design a program to check the status of SW and perform the following tasks:
   (a)If SW is pressed, LED ON,
   (b)If SW is not pressed, LED OFF.
   Note. You can assign whatever pins you wish to meet the requirements.
*/

AGAIN: JB P1.2, OVER
SETB P2.0
SJMP AGAIN
OVER: CLR P2.0
SJMP AGAIN
END
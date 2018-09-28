Timer A Blink by Alex Marino
Embedded Systems Section 3
Due by September 28, 2018
Created September 19, 2018
Version 1.0 - Lasted updated September 27, 2018
Supported Boards: MSP430G2553, MSP430FR2311
###############################################
Included files:
main.c
README.txt
Also required: msp430.h
###############################################
The purpose of this program is to make two LEDs blink at different frequencies using timers. This 
requires two LEDs to be set as output pins, but no input was required. Two timers were also 
initialized. These were set to use the SMCLk with an 8 divider in up mode. The capture compare 
register 0 for each timer was initialized at two different values to make the LEDs flash at 
different rates. Capture compare interrupt was also enabled for each timer to allow the interrupt 
service routines to toggle the LEDs. The program used one interrupt service routine for each LED, 
which were set to trigger upon reaching the CCR0 value of each timer. The G2553 uses P1.0 and P1.6
as LED outputs, and uses TA0 and TA1 for timing. The FR2311 uses P1.0 and P2.0 as LED outputs and 
timers TB0 and TB1. 

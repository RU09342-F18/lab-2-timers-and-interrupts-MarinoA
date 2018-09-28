Button Interrupt by Alex Marino
Embedded Systems Section 3
Due by September 28, 2018
Created September 19, 2018
Version 1.0 - Lasted updated September 27, 2018
Supported Boards: MSP430G2553, MSP430F5529
###############################################
Included files:
main.c
README.txt
Also required: msp430.h
###############################################
The purpose of this program is to enable an LED when the button is pressed. 
The program sets an LED pin as output and then a switch pin as the input. Interrupt 
and a pull up resistor also need to be enabled on the switch pin. The interrupt service 
routine checks the port 1 vector for a button press, and toggles the LED when this event 
occurs. The interrupt flag is also cleared so that the routine can be used again for 
subsequent button presses. The input pin for the G2553 is P1.3, while the output pin is 
P1.0. For the F5529, the input is P1.1 and the output is P1.0. 

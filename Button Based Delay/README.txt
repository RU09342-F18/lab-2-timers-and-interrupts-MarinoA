Button Based Delay by Alex Marino
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
The purpose of this program is to flash an LED at a rate set but a user holding a button. Holding 
the button for a certain amount of time and then releasing it causes the LED to be enabled for the 
same amount of time. This required the LED pin to be set as output and the button to be set as input.
An additional LED was set as an output for testing purposes but this was not required and should be 
omitted for final deployment. The interrupt for the button was enabled for falling edge detection. 
A pull up resistor was also enabled on the switch, and the interrupt flag for this pin was also cleared.
For timer control, ACLK with a divide by 2 was selected in count up mode. The interrupt for capture 
compare zero was also enabled and an initial value was set. Low power mode 0 and global interrupt were 
both enabled as well. In the timer interrupt service routine, the LED was toggled. In the port 1 (button)
interrupt service routine, an if statement checked whether there was a falling or rising edge. On a 
falling edge, the P1 interrupt edge select was changed to look for a rising edge. THe Timer was cleared 
and was set to continuous mode. For testing, an LED was also toggled in order to visually identify that 
a falling edge was detected. If a falling edge was not detected, the test LED was turned off, the
timer was stopped, and the current value of the timer was stored in the CCR0. This means that the amount 
of time the button was held down for can now be counted back up to. In order to do so, the timer mode was
changed back to up, and falling edge detection was reenabled. Finally, the interrupt flag on P1.3 is 
cleared outside of the if statement. Once the interrupt routinue is completed, the timer will now be in
up mode counting up to the value stored while the timer was in continuous mode. 
The G2553 uses P1.0 as the main output LED and P1.6 as the test LED. The switch is on P1.3, and timer A0
was used. For the F5529, P1.0 is the primary LED output and P4.7 is the test LED. The switch is on P1.1 
and the timer used was B0. 


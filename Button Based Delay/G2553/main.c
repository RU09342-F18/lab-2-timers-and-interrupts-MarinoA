//G2553 Button Based Delay
#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
    BCSCTL3 = LFXT1S_2;                        //tells MC to use internal crystal
    P1DIR |= BIT0;                          //set P1.0 as out
    P1DIR &= ~BIT3;                        //set P1.3 as in
    P1DIR |= BIT6;                             //set P1.6 to out
    P1IE |=  BIT3;                            // P1.3 interrupt enabled
    P1IES |= BIT3;                            // P1.3 falling edge
    P1REN |= BIT3;                            // Enable Pull Up on SW2 (P1.3)
    P1OUT |= BIT3;                              //sets pull up resistor
    P1IFG &= ~BIT3;                           // P1.3 IFG cleared

    //set up timer
    TA0CTL = TASSEL_1 + ID_1 + MC_1; //Timer 0 control = ACLK, divide by 2, count up to CCR0

    //set up CCR1
    CCTL0 =CCIE;  //enable capture compare interrupt
    CCR0 = 300; //change period

	_BIS_SR(LPM0_bits + GIE);   //enable global interrupt
	return 0;
}

//interrupt routine for timer
#pragma vector =TIMER0_A0_VECTOR
__interrupt void TIMER0_A1(void)
{

    P1OUT ^= BIT0; //toggle P1.0 LED

}


//interrupt routine for button
#pragma vector =PORT1_VECTOR
__interrupt void Button_down(void)
{
    if (P1IES & BIT3) //if falling edge
    {
        P1IES &=~BIT3; //change to rising edge
        TACTL=TACLR; //clear timer
        TA0CTL = TASSEL_1 + ID_1 + MC_2; //change to continuous
        P1OUT |= BIT6; //checks to see if we're in the if statement
    }

    else
    {
        P1OUT &= ~BIT6; //turn off if statement test LED
        TA0CTL = MC_0; // stop timer
        CCR0 = TA0R; //set CCR0 to current timer value
        TACTL |= TACLR; //clear timer
        TA0CTL = TASSEL_1 + ID_1 + MC_1; //change to up mode
        P1IES |= BIT3; //change to falling edge detect
    }

    P1IFG &= ~BIT3; // clear interrupt flag
}


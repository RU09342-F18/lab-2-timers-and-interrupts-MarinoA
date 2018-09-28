//F5529 Button Based Delay
#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

    P1DIR |= BIT0;                             //set P1.0 as out
    P1DIR &= ~BIT1;                            //set P1.1 as input
    P4DIR |= BIT7;                             //set P4.7 as out
    P1IE |=  BIT1;                            // P1.1 interrupt enabled
    P1IES |= BIT1;                            // P1.1 falling edge
    P1REN |= BIT1;                            // Enable Pull Up P1.1
    P1OUT |= BIT1;                             //set resistor as pull up
    P1IFG &= ~BIT1;                           // P1.1 IFG cleared

    //set up timer
    TB0CTL = TASSEL_1 + ID_3 + MC_1; //Timer 0 control = ACLK, divide by 8, count up to CCR0

    //set up CCR1
    TB0CCTL0 =CCIE;  /* Timer0_A1 Capture/Compare Control 0 */

    TB0CCR0 = 300; //change period

    _BIS_SR(LPM0_bits + GIE);   //enable global interrupt
    return 0;
}

//interrupt routine for timer
#pragma vector =TIMER0_B0_VECTOR
__interrupt void TIMER0_A1(void)
{

    P1OUT ^= BIT0; //toggle P1.0 LED

}


//interrupt routine for button
#pragma vector =PORT1_VECTOR
__interrupt void Button_down(void)
{
    if (P1IES & BIT1) //if falling edge
    {
        P1IES &=~BIT1; //change to rising edge
        TBCTL=TBCLR; //clear timer
        TB0CTL = TASSEL_1 + ID_3 + MC_2; //change to continuous
        P4OUT |= BIT7; //checks to see if we're in the if statement
    }

    else
    {
        P4OUT &= ~BIT7; // turn off LED on P4.7
        TB0CTL = MC_0; //turn off timer
        TB0CCR0 = TB0R; //set CCR to current timer value
        TBCTL |= TBCLR; //clear timer
        TB0CTL = TASSEL_1 + ID_3 + MC_1; //change to up mode
        P1IES |= BIT1; //change to detect falling edge
    }

    P1IFG &= ~BIT1; //clear flag
}


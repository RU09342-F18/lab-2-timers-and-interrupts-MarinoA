//FR2311 Timer A

#include <msp430.h> 

void main (void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
    P1DIR |= BIT0; //set P1.0 as out
    P2DIR |= BIT0; //set P2.0 as out

    //set up timer
    TB0CTL = TBSSEL_2 + ID_3 + MC_1;  //Timer 0 control = SMCLK, divide by 8, count up to CCR0
    TB1CTL = TBSSEL_2 + ID_3 + MC_1;  //Timer 0 control = SMCLK, divide by 8, count up to CCR0

    //set up CCR1
    TB0CCTL0 = CCIE; //enable capture compare interrupt
    TB1CCTL0 = CCIE; //enable capture compare interrupt
    TB0CCR0=0x07000;//set period of timer 0
    TB1CCR0=0x04000;//set period of timer 1

    __bis_SR_register(GIE);   //enable global interrupt
    while(1);
}

//interrupt service routine
#pragma vector =TIMER0_B0_VECTOR
__interrupt void TIMER0_B1(void)
{

    P1OUT ^= BIT0; //toggle LED P1.0

}


//interrupt service routine
#pragma vector =TIMER1_B0_VECTOR
__interrupt void TIMER1_A0(void)
{

    P2OUT ^= BIT0; //toggle LED P2.0

}

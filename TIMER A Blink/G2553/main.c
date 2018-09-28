//G2553 Timer A

#include <msp430.h> 

void main (void)
{
    WDTCTL = WDTPW + WDTHOLD;       // Stop watchdog timer
    BCSCTL3 = LFXT1S_2;             //tells MC to use internal crystal
    P1DIR |= BIT0;                  //set P1.0 as out
    P1DIR |= BIT6;                  //set P1.6 as out

    //set up timer
    TA0CTL = TASSEL_2 + ID_3 + MC_1;        //Timer 0 control = SMCLK, divide by 8, count up to CCR0
    TA1CTL = TASSEL_2 + ID_3 + MC_1;        //Timer 1 control = SMCLK, divide by 8, count up to CCR0

    //set up CCR1
    TA0CCTL0 = CCIE; //enable capture compare interrupt
    TA1CCTL0 = CCIE; //enable capture compare interrupt
    TA0CCR0=0x07000; //set period of timer 0
    TA1CCR0=0x04000; //set period of timer 1

    __bis_SR_register(GIE);   //enable global interrupt
    while(1);
}

//interrupt service routine 0
#pragma vector =TIMER0_A0_VECTOR
__interrupt void TIMER0_A1(void)
{

    P1OUT ^= BIT0; //toggle LED P1.0

}


//interrupt service routine 1
#pragma vector =TIMER1_A0_VECTOR
__interrupt void TIMER1_A0(void)
{

    P1OUT ^= BIT6; //toggle LED P1.6

}

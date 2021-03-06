//F5529 Button Blink
//http://processors.wiki.ti.com/index.php/MSP430_LaunchPad_Interrupt_vs_Polling

//******************************************************************************
//  MSP430G2xx3 Demo - Software Port Interrupt Service on P1.3 from LPM4
//
//  Description: A hi/low transition on P1.3 will trigger P1_ISR which,
//  toggles P1.0. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
//  with the LED removed, all unused P1.x/P2.x configured as output or inputs
//  pulled high or low, and ensure the P1.3 interrupt input does not float.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430G2xx3
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.3        P1.0|-->LED
//     \|/
//
//  F. Chen
//  Texas Instruments, Inc
//  November 2012
//  Built with CCS Version 5.2.1 and IAR Embedded Workbench Version: 5.51.1
//******************************************************************************
#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  P1IE |=  BIT1;                            // P1.1 interrupt enabled
  P1IES |= BIT1;                            // P1.1 falling edge
  P1REN |= BIT1;                            // Enable Pull Up on SW1 (P1.1)
  P1IFG &= ~BIT1;                           // P1.1 IFG cleared
                                            //BIT1 on Port 1 can be used as Switch1


  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)//check compiler version
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else
#error Compiler not supported!
#endif
{
  P1OUT ^= BIT0;                            // P1.0 = toggle
  P1IFG &= ~BIT1;                           // P1.1 IFG cleared
}

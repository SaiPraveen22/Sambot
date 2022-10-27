#include <msp430.h>
#include "adc.h"







int cntr.1 = 0;
int cntr.2 = 0;
int timer_a_counter = 0;



int flag = 0;



int setpoint = 3;



int delta = 0;



void motor(int);



void main()
{
    WDTCTL = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CAL_DCO_1MHZ;



    P2DIR |= (BIT1 | BIT2 | BIT4 | BIT5);
    P2SEL |= (BIT2 | BIT4 );
    P1DIR &= ~(BIT1 | BIT4);



    P2OUT &= ~(BIT1);



    P2DIR &= ~(BIT0 | BIT3);



    P1DIR &= ~(BIT1 | BIT4);



    init_adc(2);
    init_adc(4);



    TA1CCR0 = 6;
    TA1CCR1 = 0;
    TA1CCR2 = 0;



    TA1CCTL1 |= (OUTMOD_7);
    TA1CCTL2 |= (OUTMOD_7);
    TA1CTL |= (TASSEL_2 | ID_3 | MC_1);



    __enable_interrupt();



    while(1)
    {
        cntr.1 = read_adc(2);
        cntr.2 = read_adc(4);



      if((cntr.1 < 700) && (cntr.2 < 700))            //center state , both are on white line
            flag = 3;
        else if((cntr.1 < 700) && (cntr.2 > 700))       //off to left state, left sensor goes blank, right is on line
            flag = 2;
        else if((cntr.1 > 700) && (cntr.2 < 700))
            flag = 1;                                   //off to right state, right sensor goes blank, left is on line



        motor(flag);



    }
}



void motor(int output)
{
    switch(output)
    {
    case 3:
        TA1CCR1 = 1;
        TA1CCR2 = 1.2;
        __delay_cycles(10000);
        break;



        case 2:
        TA1CCR1 = 0;
        TA1CCR2 = 1;
        __delay_cycles(10000);
        break;



        case 1:
        TA1CCR1 = 1;
        TA1CCR2 = 0;
        __delay_cycles(10000);
        break;
    }
}



#pragma vector=PORT2_VECTOR
__interrupt void port_2(void)
{
    if((P2IFG == BIT0) && (P2IFG != BIT3))
    {
        ++cntr.1;
        P2IFG = 0;
    }



    if((P2IFG == BIT3) && (P2IFG != BIT1))
    {
        ++cntr.2;
        P2IFG = 0;
    }
}



#pragma vector=TIMER0_A1_VECTOR
__interrupt void interrupt_timerA(void)
{

}

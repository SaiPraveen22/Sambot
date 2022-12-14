
#include <adc.h>
void init_adc( unsigned int channel )
{
   unsigned int BIT_X = 0, INCH_X = 0;
   if(channel == 0 ) {BIT_X = BIT0; INCH_X = INCH_0;}
   if(channel == 1 ) {BIT_X = BIT1; INCH_X = INCH_1;}
   if(channel == 2 ) {BIT_X = BIT2; INCH_X = INCH_2;}
   if(channel == 3 ) {BIT_X = BIT3; INCH_X = INCH_3;}
   if(channel == 4 ) {BIT_X = BIT4; INCH_X = INCH_4;}
   if(channel == 5 ) {BIT_X = BIT5; INCH_X = INCH_5;}
   if(channel == 6 ) {BIT_X = BIT6; INCH_X = INCH_6;}
   if(channel == 7 ) {BIT_X = BIT7; INCH_X = INCH_7;}



   P1DIR &= ~BIT_X;
   ADC10AE0 = BIT_X;
   ADC10CTL1 = INCH_X + ADC10DIV_0;
   ADC10CTL0 = SREF_0 + ADC10SHT_2 + REFON + ADC10ON;
}





unsigned int read_adc( unsigned int sensor )
{
  init_adc( sensor );
  ADC10CTL0 |= ENC | ADC10SC;
  while( !(ADC10CTL0 & ADC10IFG) || (ADC10CTL1 & ADC10BUSY) );
  ADC10CTL0 &= ~( ENC | ADC10IFG);
  return ADC10MEM;
}

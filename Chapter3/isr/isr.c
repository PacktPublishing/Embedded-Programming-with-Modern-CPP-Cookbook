#include<mcs51reg.h> 

volatile int Counter = 0;
void timer0_ISR (void) __interrupt(1) //interrupt no. 1 for Timer0 
{ 
 
  Counter++;
} 

void main(void) 
{ 
  TMOD = 0x03; 
  TH0 = 0x0; 
  TL0 = 0x0; 
  ET0 = 1; 
  TR0 = 1;
  EA = 1;
  while (1); // do nothing 
} 

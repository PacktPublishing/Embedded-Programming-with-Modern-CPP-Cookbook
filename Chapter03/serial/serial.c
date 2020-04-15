#include<8051.h>

unsigned char receivedChar=0;

void serial_isr() __interrupt(4) { 
    if(RI == 1) {
        P0 = SBUF;
        RI = 0;
    } else if(TI == 1) {
        TI = 0;
    }
}


void main() {
    SCON = 0x50;
    TMOD = 0x20;
    TH1 =  0xFD;
    TR1 = 1;     
    ES  = 1;
    EA  = 1;

    while(1);
}
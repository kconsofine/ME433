#include "nu32dip.h"

void RCsetup();
void delay(int time);

int main() {
    int i = 0;
    NU32DIP_Startup();
    RCsetup();
    while (1)
    {
        if (i == 100)
            i = 0;
        OC1RS = 3000 + 30*i;
        i++;
        delay(40);

    }
}

void RCsetup(){
    T2CONbits.TCKPS = 0b100;     // Timer2 prescaler N=4 (1:4)
    PR2 = 59999;              // period = (PR2+1) * N * (1/48000000) = 6 kHz
    TMR2 = 0;                // initial TMR2 count is 0
    RPA0Rbits.RPA0R = 0b0101; // set A0 to be OC1.
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 1000;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC1R = 1000;              // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1
     
}

void delay(int ms) {
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < ms*24000)
    {}
    
}
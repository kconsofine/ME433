
#include <proc/p32mx170f256b.h>
#include "spi.h"


// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1
    
    
    // Turn of analog pins
    //...
    ANSELB = 0;
    ANSELA = 0;
    // Make an output pin for CS
    //...
    TRISBbits.TRISB6 = 0; // choose B6 to be CS
    LATBbits.LATB6 = 0; // set low;
    //...
    // Set SDO1
    RPA1Rbits.RPA1R = 0b0011; // A1 is SDO1
    //...
    // Set SDI1
    //...
    SDI1Rbits.SDI1R = 0b0010;

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    SPI1BRG = 1000; // 1000 for 24kHz, 1 for 12MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.ON = 1; // turn on spi 
}


// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}
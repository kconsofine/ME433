#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>
#include "spi.h"



void sendData(int val, int AB);
void delay();

int main(void) {
  char message[100];
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  initSPI(); // init spi
  
  int sinvals[200];
  int trivals[200];
  for (int i = 0; i < 200; i++)
  {
      float tempsin = (sin((i / 100.0) * 2 * 3.1415) + 1);
      int tempsin1 = (int)(tempsin * 1023 / 2);
      sinvals[i] = tempsin1;
      if (i < 100) 
      {
          trivals[i] = 10*i;
      }
      else 
      {
          trivals[i] = 1000 - 10 * (i - 100);
      }
      

    {}
  }
  int i = 0;
  while (1) {
    _CP0_SET_COUNT(0);

      CS = 0;
      sendData(trivals[i],1);
      CS = 1;
      CS = 0;
      sendData(sinvals[i],0);
      CS = 1;

      while (_CP0_GET_COUNT() < 48000000 / 2 / 200)
    {}
      i++;
      if (i == 200)
      {
          i = 0;
      }
      
      
      
  }
}

void sendData(int Val, int AB)
{
    if (AB == 0)
    {
        unsigned short t = 0;
        t = 0b0111<<12;
        t = t|(Val<<2);
        spi_io(t>>8);
        spi_io(t);
    }
    else 
    {
        unsigned short t = 0;
        t = 0b1111<<12;
        t = t|(Val<<2);
        spi_io(t>>8);
        spi_io(t);  
    }
    
}

void delay()
{

}

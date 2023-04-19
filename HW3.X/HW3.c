#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>

int main(void) {
  char message[100];
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
	if (!NU32DIP_USER){
		for (int i = 0; i< 100; i++)
        {
            double output = (sin(2*3.14152*i/100)+1)*3.3/2;
            sprintf(message,"%f\r\n",output);
            NU32DIP_WriteUART1(message);
            _CP0_SET_COUNT(0);
            while (_CP0_GET_COUNT() < 240000)
            {}
        }
	}
  }
}


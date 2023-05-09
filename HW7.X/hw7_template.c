#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include <stdio.h>
#define WHOAMI 0x68
#define MAXG 2

void blink(int, int); // blink the LEDs function

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    i2c_master_setup();
    init_mpu6050();
    char message[100];
	
	// char array for the raw data
    char data[14]; 
    float floatData[7];
	// floats to store the data
	
	// read whoami
    char who = whoami();
	// print whoami
    sprintf(message,"%x\r\n",who);
    NU32DIP_WriteUART1(message);
    
	// if whoami is not 0x68, stuck in loop with LEDs on
    if (who != 0x68)
    {
        while (1)
        {
            NU32DIP_GREEN = 0;
            NU32DIP_YELLOW = 0;
        }
    }
    
	// wait to print until you get a newline
    NU32DIP_ReadUART1(message,100);

    while (1) {
		// use core timer for exactly 100Hz loop
        _CP0_SET_COUNT(0);
        blink(1, 5);

        // read IMU
        burst_read_mpu6050(data);
		// convert data
        float floatData[7];
        floatData[0] = conv_xXL(data);
        floatData[1] = conv_yXL(data);
        floatData[2] = conv_zXL(data);
        floatData[3] = conv_temp(data);
        floatData[4] = conv_xG(data);
        floatData[5] = conv_yG(data);
        floatData[6] = conv_zG(data);
        
        //sprintf(message,"%f %f %f %f %f %f %f\r\n",floatData[0],floatData[1],floatData[2],floatData[3],floatData[4],floatData[5],floatData[6]);
        sprintf(message,"%f\r\n",floatData[2]);
        NU32DIP_WriteUART1(message);

        // print out the data

        while (_CP0_GET_COUNT() < 48000000 / 2 / 100) {
        }
    }
}

// blink the LEDs
void blink(int iterations, int time_ms) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        NU32DIP_GREEN = 0; // on
        NU32DIP_YELLOW = 1; // off
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }

        NU32DIP_GREEN = 1; // off
        NU32DIP_YELLOW = 0; // on
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}




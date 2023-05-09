#include <stdio.h>
#include "nu32dip.h"
#include "ssd1306.h"
#include "font.h"
#include "mpu6050.h"


void drawChar(unsigned char x, unsigned char y, unsigned char character);
void drawString(unsigned char x, unsigned char y, char* string);
float getAcc(void);
void drawAcc();
void blink(int iterations, int time_ms);

int main() {
    
    NU32DIP_Startup();
    i2c_master_setup();
    ssd1306_setup();
    init_mpu6050();
    char message[100];
	
	// char array for the raw data
    
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
    
    while (1)
    {
        _CP0_SET_COUNT(0);
        blink(1,1);
        ssd1306_clear();
        //ssd1306_drawPixel(0,0,1);
        //drawChar(10,10,0x48);
        //drawString(10,10,"hello");
        drawAcc();
        ssd1306_update();
        float FPS = 1/((_CP0_GET_COUNT()/48000000.0)*2);
        sprintf(message,"%f frames per second",FPS);
        drawString(0,24,message);
        ssd1306_update();
    }
    
    
}

void drawChar(unsigned char x, unsigned char y, unsigned char character)
{
    unsigned char newChar = character - 32;
    for (int i = 0;i < 5; i++)
    {
        char col = ASCII[newChar][i];
        for (int j = 0;j < 8;j++)
        {
            char onOff = (col>>j)&0b1;
            ssd1306_drawPixel(x+i, y+j, onOff);
        }
    }
}

void drawString(unsigned char x, unsigned char y, char* string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        if (x > 124)
        {
            x = 0;
            y += 8;
        }
        drawChar(x, y, string[i]);
        x+=5;
        i++;
    }
}

void drawAcc(void)
{
    char acc[100];
    sprintf(acc,"%f",getAcc());
    drawString(0,0,acc);
}

float getAcc(void)
{
    char data[14]; 
    burst_read_mpu6050(data);
    float zXL = conv_zXL(data);
    return zXL;
}
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


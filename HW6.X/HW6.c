#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>
#include "i2c_master_noint.h"
#define GPIO 0x09
#define OLAT 0x0A
#define IODIR 0x00
#define addr 0b01000000



void extenderSetup();
void genericI2Cwrite(unsigned char add, unsigned char reg, unsigned char val);
unsigned char genericI2Cread(unsigned char add, unsigned char reg);
int getButton();
void blink();

int main(void) {
    char message[100];
    i2c_master_setup();
    extenderSetup();
    
    while (1)
    {
        blink();
        int rec = getButton();
        if (rec == 0)
        {
            genericI2Cwrite(addr,OLAT,0b10000000);
            
        }
        else 
        {
            genericI2Cwrite(addr,OLAT,0b00000000);
        }
    }
    
}

// add is the write address
void genericI2Cwrite(unsigned char add, unsigned char reg, unsigned char val)
{

    i2c_master_start();
    i2c_master_send(add);
    i2c_master_send(reg);
    i2c_master_send(val);
    i2c_master_stop(); 
}
// add is the write address
unsigned char genericI2Cread(unsigned char add, unsigned char reg)
{
    unsigned char addR = add|0b00000001;
    i2c_master_start();
    i2c_master_send(add);
    i2c_master_send(reg);
    i2c_master_restart();
    i2c_master_send(addR);
    unsigned char rec = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    return rec;
}
void extenderSetup()
{
    genericI2Cwrite(addr,IODIR,0b00000001);
}

void blink()
{
    NU32DIP_YELLOW = 1;
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < 48000000 / 2 / 20) {}
    NU32DIP_YELLOW = 0;
}

int getButton()
{
    unsigned char rec = genericI2Cread(addr,GPIO);
    rec = rec & 0b1;
    return (int)rec;
}

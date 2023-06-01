#include "ws2812b.h"
#include "nu32dip.h"
#define RAINBOW_PRECISION 1000

void rainbowSetup(wsColor* rainbow,int i);
void delay();

int main() {
    NU32DIP_Startup();
    ws2812b_setup();
    wsColor rainbow[5];
    int i = 0;
    while (1)
    {
        if (i == RAINBOW_PRECISION)
        {
            i = 0;
        }
        rainbowSetup(rainbow,i);
        ws2812b_setColor(rainbow,5);
        i++;
    }
}

void rainbowSetup(wsColor* rainbow,int i)
{
    int diff = 360/12;
        float hue = 360.0/RAINBOW_PRECISION;
        for (int j = 0; j < 5;j++)
        {
            int hueI = (int)(hue*i + diff*j);
            hueI = hueI % 360;
            float hueF = (float)hueI;
            rainbow[j] = HSBtoRGB(hueF,1.0,0.5);
            
        }
}
void delay()
{
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<24000000*0.02)
    {}
    
    
}

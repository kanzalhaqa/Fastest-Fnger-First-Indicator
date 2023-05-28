#include <reg51.h>
#include "I2C.h"

sbit SCL=P3^6;
sbit SDA=P3^7;

void I2C_Clock(void)
{
	delay(.001);
	SCL=1;
	
	delay(.001);
	SCL=0;
}
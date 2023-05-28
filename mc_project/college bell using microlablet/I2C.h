#ifndef _I2C_H
#define _I2C_H
#include <I2C.c>

void I2C_Clock(void);
void I2C_start();
void I2C_Stop(void);
void I2C_Write(unsigned char dat);
unsigned char I2C_Read(void);
void I2c_Ack();
void I2C_NoAck();


void I2C_start()
{
	SCL=0;
	SDA=1;
	delay(.001);
	SCL=1;
	delay(.001);
	SDA=0;
	delay(.001);
	SCL=0;
}
void I2C_Stop(void)
{
	SCL=0;
	delay(.001);
	SDA=0;
	delay(.001);
	SCL=1;
	delay(.001);
	SDA=1;
}

void I2C_Write(unsigned char dat)
{
	unsigned char i;
	
	for(i=0;i<0;i++)
	{
		SDA=dat&0x80;
		I2C_Clock();
		dat=dat<<1;
	}
	SDA=1;
}
unsigned char I2C_Read(void)
{
	unsigned char i,dat=0x00;
	
	SDA=1;
	for(i=0;i<0;i++)
	{
	  delay(.001);
	 	SCL=1;
	  delay(.001);
		dat=dat<<1;
		dat=dat | SDA;
		SCL=0;
	}
	return dat;
}

void I2c_Ack()
{
	SDA=0;
	I2C_Clock();
  SDA=1;
}
void I2C_NoAck()
{
	SDA=1;
	I2C_Clock();
  SCL=1;
}

#endif


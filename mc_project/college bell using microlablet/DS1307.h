#ifndef _DS1307_H
#define _DS1307_H
#include <ds1307.c>

void DS1307_init();
void DS1307_Write(unsigned char);
unsigned char DS1307_Read();
void DS1307_SetTime(unsigned char ss,unsigned char mm, unsigned char hh);
void DS1307_SetDate(unsigned char dd,unsigned char mm, unsigned char yy);
void DS1307_GetTime( char *h_ptr, char *m_ptr,  char *s_ptr);
void DS1307_GetDate( char *d_ptr, char *m_ptr,  char *y_ptr);


void DS1307_init()
{
  I2C_start();
	DS1307_Write(DS1307_ID);
	DS1307_Write(CONTROL);
	DS1307_Write(0x00);
	I2C_Stop();
}
void DS1307_write(unsigned char dat)
{
	I2C_Write(dat);
	I2C_Clock();
}
unsigned char DS1307_Read()
{
	unsigned char dat;
	dat=I2C_Read();
	return(dat);
}
void DS1307_SetTime(unsigned char ss,unsigned char mm, unsigned char hh)
{
	I2C_start();
	
	DS1307_Write(DS1307_ID);
	DS1307_Write(SEC_ADDRESS);
	DS1307_Write(ss);
	DS1307_Write(mm);
	DS1307_Write(hh);
	
	I2C_Stop();
}
void DS1307_SetDate(unsigned char dd,unsigned char mm, unsigned char yy)
{
	I2C_start();
	
	DS1307_Write(DS1307_ID);
	DS1307_Write(DATE_ADDRESS);
	DS1307_Write(dd);
	DS1307_Write(mm);
	DS1307_Write(yy);
	
	I2C_Stop();
}
void DS1307_GetTime(unsigned char *h_ptr,unsigned char *m_ptr, unsigned char *s_ptr)
{
	I2C_start();
	
	DS1307_Write(DS1307_ID);
	DS1307_Write(SEC_ADDRESS);
	
	I2C_Stop();
	
  I2C_start();
	DS1307_Write(0xD1);
	
	*s_ptr=DS1307_Read();
	I2c_Ack();
	
  *m_ptr=DS1307_Read();
	I2c_Ack();
	
	*h_ptr=DS1307_Read();
	I2C_NoAck();
	
	I2C_Stop();
}
void DS1307_GetDate(unsigned char *d_ptr,unsigned char *m_ptr, unsigned char *y_ptr)
{
	I2C_start();
	
	DS1307_Write(DS1307_ID);
	DS1307_Write(DATE_ADDRESS);
	
	I2C_Stop();
	
  I2C_start();
	DS1307_Write(0xD1);
	
	*d_ptr=DS1307_Read();
	I2c_Ack();
	
  *m_ptr=DS1307_Read();
	I2c_Ack();
	
	*y_ptr=DS1307_Read();
	I2C_NoAck();
	
	I2C_Stop();
}

#endif


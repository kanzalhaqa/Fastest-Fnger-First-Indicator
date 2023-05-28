#include <reg51.h>
#include "DS1307.h"

void main()
{
	unsigned char sec, min, hour, day, month, year;
	//lcd init
	DS1307_Init();
	DS1307_SetTime(0x10,0x40,0x20); //set time once and load it to rtc then comment two code and redump code
	DS1307_SetDate(0x12,0x07,0x14);
	LCD_DisplayString("Time: ");
	LCD_GoTolineTwo();
	LCD_displayString("Date: ");
	while(1)
	{
		DS1307_GetTime(&hour,&min,&sec);
		Lcd_gotoXY(0,6);
		lcd_displayRtcTime(hour,min,sec);
		DS1307_GetDate(&day,&month,&year);
		lcd_gotoXY(1,6);
		LCD_DisplayRtcDate(day,month,year);
		
	}
}
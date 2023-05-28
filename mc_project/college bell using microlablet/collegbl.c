#include <MicroLABlet.h>
#include <readkey.c>
#define control_register 0x00
#define data_register 0x01
#define LCD_data P1
#define first_line 0x80
#define second_line 0xC0

sbit LCD_enable=P3^7;
sbit LCD_register_select=P3^6;
sbit press_1=P3^4;
sbit press_0=P3^2;
sbit relay_control_signal=P2^0;
enable=0;

unsigned char message_three[]={"BackUp :press S1"};
unsigned char message_four[] ={"SetTime:press S4"};
unsigned char message_five[] ={"Date -01/01/2022"};
unsigned char message_six[]  ={"Time - 00:00:00 "};
unsigned char ascii[]="0123456789";

unsigned char check,HourH,HourL,DateH,DateL,MonthH,MonthL,YearH,YearL,MinH,MinL,SecH,SecL,SetHH4B=0,SetHL4B=0,SetMH4B=0,SetML4B=0,SetSH4B=0,SetSL4B=0;
unsigned char  cursor_count=0x86; 
unsigned char flag=0;

void LCD_Initialization();
void LCD_command_write(unsigned char command_value);
void LCD_message_write(unsigned char message_charactor);

void main ()
 {
    unsigned char charactor_count;

    LCD_Initialization();
	 
    charactor_count=0;
		LCD_command_write(0X80);
			while(message_three[charactor_count]!='\0')
				{
					LCD_message_write(message_three[charactor_count]);
					charactor_count++;
				}
				
		charactor_count=0;
		LCD_command_write(0XC0);
			while(message_four[charactor_count]!='\0')
				{
					LCD_message_write(message_four[charactor_count]);
					charactor_count++;
				}
				
 while(1)
	{
		if(press_1==1 | press_0==0)
			{
				break;
			}
	}
	
 while(1)
	{
		if(press_1==1)
			{
				flag=1;
			}
			
		if(press_0==0)
			{
				flag=0;
			}
			
		if(flag==1)
			{	
				charactor_count=0;
				LCD_command_write(0X80);
				while(message_five[charactor_count]!='\0')
					{
						LCD_message_write(message_five[charactor_count]);
						charactor_count++;
					}
					
				charactor_count=0;
				LCD_command_write(0XC0);
				while(message_six[charactor_count]!='\0')
					{
						LCD_message_write(message_six[charactor_count]);
						charactor_count++;
					}
				goto timeSection;
			}

	  if(flag==0)
			{
				charactor_count=0;
				LCD_command_write(0X80);
					while(message_five[charactor_count]!='\0')
						{
							LCD_message_write(message_five[charactor_count]);
							charactor_count++;
						}
						
				charactor_count=0;
				LCD_command_write(0XC0);
					while(message_six[charactor_count]!='\0')
						{
							LCD_message_write(message_six[charactor_count]);
							charactor_count++;
						} 
 
				for(cursor_count=0x86;cursor_count<=0xCF;cursor_count++)
					{
						LCD_command_write(cursor_count);  
						LCD_command_write(0X0f);
						delay(500);
						key_value=readkey();
						LCD_command_write(cursor_count);
						LCD_message_write(ascii[key_value]);
							if (cursor_count==0x86)
								{
									DateH=key_value;
								}
							if (cursor_count==0x87)
								{
									DateL=key_value;			 
								}		 
							if (cursor_count==0x89)
								{
									MonthH=key_value;
								}
							if (cursor_count==0x8A)
								{
									MonthL=key_value;
									cursor_count=0xC6;
								}		 
							if (cursor_count==0xC7)
								{
									HourH=key_value;
								}
							if (cursor_count==0xC8)
								{
									HourL=key_value;
								}
							if (cursor_count==0xCA)
								{
									MinH=key_value;
								}
							if (cursor_count==0xCB)
								{
									MinL=key_value;
								}		 
							if(cursor_count==0xCB)
								{
									cursor_count=0XCF;
									LCD_command_write(cursor_count);
								}
							if(cursor_count==0x87 | cursor_count==0x8A | cursor_count==0xC8 |cursor_count==0xCB )
								{
									cursor_count++;
								}
							if(cursor_count==0xCF)
								{
									for(check=0;check<(check+1);check++)
										{  
											if(check==0)
												{
													if(DateH>3)
														{ 
															cursor_count=0x85;
															LCD_command_write(cursor_count);
															break;
														}
													else{check=0;}
												}
												
											if(check==1)
												{
													if(DateH==3 & DateL>1)
														{ 
															cursor_count=0x86;
															LCD_command_write(cursor_count);
															break;
														}
													else{check=1;}
												}
    
											if(check==2)
												{
													if(DateH==0 & DateL==0)
														{ 
															cursor_count=0x86;
															LCD_command_write(cursor_count);
															break;
														}
													else{check=2;}
												}
												
											if(check==3)
												{
													if(MonthH>1)
														{ 
															cursor_count=0x88;
															LCD_command_write(cursor_count);
															break;
														}
													else{check=3;}
												}
												
											if(check==4)
												{
													if(MonthH==1 & MonthL>2)
														{ 
															cursor_count=0x89;
															LCD_command_write(cursor_count);
															break;
														}
													else{check=4;}
												}

											if(check==5)
												{
													if(MonthH==0 & MonthL==0)
														{ 
															cursor_count=0x89;
															LCD_command_write(cursor_count);
															break;
														}
													else{check=5;}
												}
												
											if(check==6)
												{
													if(HourH>2)
														{ 
															cursor_count=0xC6;
															LCD_command_write(cursor_count);
															break;
														}
													else{check=6;}
												}
											 
											if(check==6)
												{
													if(HourH==2 & HourL>3)
														{ 
															cursor_count=0xC7;
															LCD_command_write(cursor_count);
															break;
														}
													else{check=6;}
												}
											
											if(check==7)
												{
													if(MinH>5)
														{ 
															cursor_count=0xC9;
															LCD_command_write(cursor_count);
															break;
														}
													else{check=7;}
												}

											if(check==8)
												{ 
													timeSection:
					 
														flag=11;
														LCD_command_write(0x0C);
														while(1)
															{
																/////////Hour H//////////
																for(HourH=HourH;HourH<3;HourH++)
																	{	 
																//////////// Hour LLLLLLLLLLLL/////////////////		 
																		for(HourL=HourL;HourL<10;HourL++)
																			{
																				///////// Minute H /////////////////////////
																				for(MinH=MinH;MinH<6;MinH++)
																					{			
																						//////Minute LLLLLLLLLLLLL///////////////////////
																						for(MinL=MinL;MinL<10;MinL++)
																							{		 
																							///////////// Sec H  HHHH//////////////
																								for(SecH=0;SecH<6;SecH++)
																									{	 
																										//////////   Sec LLLLLLL//////
																										for(SecL=0;SecL<10;SecL++)
																											{	 
																												LCD_command_write(0xCE);
																												LCD_message_write(ascii[SecL]);
																												delay(910);
																													if((HourL==SetHL4B &  MinL==(SetML4B+1) & SecH==(SetSH4B+1))&(HourH==SetHH4B &  MinH==SetMH4B & SecL<=SetSH4B))
																														{  enable=0;
																															if(enable==0)
																																{
																																	for(check=0;check<1;check++)
																																		{
																																			relay_control_signal=enable;
																																			delay(910);
																																			relay_control_signal=1;
																																			enable=1;
																																			SecL++;
																																		}
																																}
																																SetML4B++;
																															}
								 
																													if((HourL==9 &  MinL==0 & SecH==1)&(HourH==0 &  MinH==0 & SecL<=1))
																														{  enable=0;
																															if(enable==0)
																																{
																																	for(check=0;check<1;check++)
																																		{
																																			relay_control_signal=enable;
																																			delay(910);
																																			relay_control_signal=1;
																																			enable=1;
																																			SecL++;
																																		}
																																}
																																SetML4B++;
																															}
                                                           																													
																												}
																											//////////   Sec LLLLLLL////////		  
																											if(flag==11)
																												{
																											   	SecH++;
																													flag=22;
																												}
																										LCD_command_write(0xCD);
																										LCD_message_write(ascii[SecH]);
																										LCD_command_write(0xCE);
																										SecL=0;
																										LCD_message_write(ascii[SecL]);
					 
																										if(flag==33)
																									{
																										 MinL--;
																											if(MinH==5)
																												{
																													MinH=0;
																												}else{MinH++;}
																												
																									 LCD_command_write(0xCB);
																									 LCD_message_write(ascii[MinL]); 
																										 flag=44;
																									 }
																									 else 
																									 {
																									 LCD_command_write(0xCB);
																									 LCD_message_write(ascii[MinL]);

																									 LCD_command_write(0xCA);
																									 LCD_message_write(ascii[MinH]);						 
																									 }

																									 if(flag==44)
																									 {
																									 LCD_command_write(0xCA);
																									 LCD_message_write(ascii[MinH]);
																										 
																									 }
																									 
																									 
																									 if(flag==55)
																											{
																												LCD_command_write(0xCA);
																												LCD_message_write(ascii[MinH]);	
																											}
																									 
																					
																									 if(MinL==0 & MinH==0 & SecH==0 & SecL==0)
																									 {
																											 if(HourL==9)
																												 {
																													 HourL=0;
																													 HourH++;
																												 } else 
																										 if(HourH==2 & HourL==3 & MinL==0 & MinH==0 & SecH==0 & SecL==0)
																									 {
																										 HourH=0;
																										 HourL=0;
																											 LCD_command_write(0xC8);
																											 LCD_message_write(ascii[HourL]);
																											 LCD_command_write(0xC7);
																											 LCD_message_write(ascii[HourH]);	
																										}
																									 else{HourL++;}
																											 LCD_command_write(0xC8);
																											 LCD_message_write(ascii[HourL]);
																											 LCD_command_write(0xC7);
																											 LCD_message_write(ascii[HourH]);	
																										}	
																									}
																									//////////////   Sec H ////////////////
																								if(MinL==9)
																									{
																										MinL=0;
																										flag=33;
																									}			
																							}
																							/////////////////////  Minute LLLLLLLLLLLLLLLL///////////////				 
																						if(MinH==6)
																							{
																								MinH=0;
																								flag=55;
																							}	
																						}
																									///////// Minute H /////////////////////////
																			if(HourL==9)
																				{
																			  	HourL=0;
																				}
																			}
																	//////////// Hour LLLLLLLLLLLL/////////////////		 
																		if(HourH==3)
																		 {
																			HourH=0;
																		 }	
																		}
	                          ////////////  Hour H //////////////////
														}
												}
										}
								}
					}
	 			 while(key_value==readkey());
		   }
	   }
   while(1);
 }

void LCD_Initialization()
 { 
     LCD_command_write(0X38);
     LCD_command_write(0X10);
     LCD_command_write(0X0C);
     LCD_command_write(0X06);
     LCD_command_write(0X01);
 }
 
void LCD_command_write(unsigned char command_value)
 {
     LCD_data= command_value;
     LCD_register_select= control_register;
     LCD_enable=1;
     delay(10);
     LCD_enable=0;
     delay(10);
 }
 
void LCD_message_write(unsigned char message_charactor)
 {
      LCD_data= message_charactor;
      LCD_register_select= data_register;
      LCD_enable=1;
      delay(10);
      LCD_enable=0;
      delay(10);
 }
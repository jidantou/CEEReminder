// main.c
#include "global.h"
#include "DS1302.h"
#include "Display.h"
#include "GUI.h"
#include "Process.h"

static u16 Timer = 0;

void main()
{
	OLED_Init();
	DS1302SetTime();
	InterruptInit();

	GUI_Start();
	OLED_Cls();

	while(1)
	{
		if(key2 == 1)
		{
			delay(1000);
			if(key2 == 1)
				KeySign ^= 0x04;
		}
		if(key3 == 1)
		{
			delay(1000);
			if(key3 == 1)
				KeySign ^= 0x08;
		}
		
		KeyPro();

		if((Timer % 500) == 0)
		{
			Process();
			DS1302ReadTime();

			if(ShowMode & 0x80)
			{
				OLED_Cls();
				ShowMode &= 0x7F;
			}
			switch(ShowMode & 0x7F)
			{
				case 0: GUI_CEE(); break;
				case 1:	GUI_Time(0); break;
				case 2:	GUI_Date(0); break;
				case 3:	GUI_CountDown(0, 0); break;
				case 4:	GUI_CountDown(1, 0); break;
				case 5:	GUI_Memu0(); break;
				case 6:	GUI_Memu1(); break;
				case 7: GUI_SetCEE(); break;
				case 8: GUI_Time(1); break;
				case 9: GUI_Date(1); break;
				case 10: GUI_CountDown(0, 1); break;
				case 11: GUI_CountDown(1, 1); break;
				default: break;
			}
		}
	}
}

void Int0() interrupt 0
{
	delay(1000);
	if(key0 == 1)
	{
		KeySign ^= 0x01;
	}
}

void Int1() interrupt 2
{
	delay(1000);
	if(key1 == 1)
	{
		KeySign ^= 0x02;
	}
}

void Timer0() interrupt 1
{
	TH0=0XFC;  //1ms
	TL0=0X18;
	Timer++;
	if(Timer == 1000)
		Timer = 0;
}

/*
// DEBUG	
//debug
void Usart() interrupt 4
{
	uchar dat;
	
	dat = SBUF;
	RI = 0;
	SBUF = dat;
	while(!TI)
		TI = 0;
	
}
*/
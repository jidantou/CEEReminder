// main.c
#include "global.h"
#include "DS1302.h"
#include "Display.h"
#include "GUI.h"
#include "Process.h"

static u16 Timer = 0, second = 0;
uchar sleep = 0;	// 0 for no sleeping

void main()
{
	OLED_Init();
	//DS1302SetTime();
	InterruptInit();
	//UsartInit();
	key0 = 1;
	key1 = 1;
	key2 = 1;
	key3 = 1;

	GUI_Start();
	delay_long(10);
	OLED_Cls();
	DS1302ReadTime();
	TR0=1;

	//UsartSend(0x88);

	while(1)
	{
		if(key2 == 0)
		{
			delay(800);
			if(key2 == 0)
			{
				while(!key2);
				KeySign |= 0x02;
				second = 0;
			}
		}
		if(key3 == 0)
		{
			delay(800);
			if(key3 == 0)
			{
				while(!key3);
				KeySign |= 0x01;
				second = 0;
			}
		}
		
		//UsartSend(0xFF);
		KeyPro();
		//UsartSend(0x00);
	}
}

void Int0() interrupt 0
{
	delay(800);
	if(key0 == 0)
	{
		while(!key0);
		if(sleep == 1)
		{
			sleep = 0;
			DS1302ReadTime();
			CountPro(0);
			CountPro(1);
		}
		else KeySign |= 0x08;
		second = 0;
	}
}

void Int1() interrupt 2
{
	delay(800);
	if(key1 == 0)
	{
		while(!key1);
		if(sleep == 1)
		{
			sleep = 0;
			DS1302ReadTime();
			CountPro(0);
			CountPro(1);
		}
		else KeySign |= 0x04;
		second = 0;
	}
}

void Timer0() interrupt 1
{
	TH0 = 0xFC;  //1ms
	TL0 = 0x18;
	Timer++;
	if(Timer % 200 == 0)
	{
		// debug
		//GUI_Test(debug);
		//delay(5000);	
		//OLED_Cls();
		//UsartSend(Timer);
		//debug = ShowMode >> 7;			

		Process();

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
			default: ShowMode = 0x00; break;
		}
	}

	if(Timer == 1000)
	{
		Timer = 0;
		second++;
		DS1302ReadTime();
		CountPro(0);
		CountPro(1);
	}

	if(second == 20)
	{
		second = 0;
		OLED_Cls();
		sleep = 1;
		PCON |= 0x02;
	}
}

/*
// DEBUG	
//debug
void Usart() interrupt 4
{
	TI = 0;
}
*/
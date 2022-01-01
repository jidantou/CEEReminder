//Global funtion
#include "reg52.h"
#include "global.h"

// Global variable
uchar CURSOR = 0x01;
// Save CEE date
uchar CEEDAY[3] = {22, 6, 7};
// Save CountDown time
uchar CountDown[2][2] = {{2, 30}, {2, 0}};
// Save current show function in GUI.c
uchar ShowMode = 0x00;
//
uchar KeySign = 0x00;
// High = 0x1 refers to ShowMode 3 pause
// Low = 0x1 refers to ShowMode 4 pause
// 0 for numbers down
uchar CountPause[2] = {1, 1};

// Save time for Count
uchar CountTime[2][2] = {{2, 3}, {2, 0}};

//if i=1, delay 10us
void delay(u16 i)
{
	while(i--);
}

void delay_long(u16 i)
{
	while(i--)
		delay(10000);
}

uchar BCDToUchar(uchar value)
{
	uchar temp = 0;
	temp = (value>>4) * 10;
	temp += value&0x0f;
	return temp;
}

uchar UcharToBCD(uchar dat)
{
	uchar i, sum = 0;
 
	for (i = 0; dat > 0; i++)
	{
		sum |= ((dat % 10 ) << ( 4 * i));
		dat /= 10;
	}
	return sum;
}


// DEBUG
void UsartInit()
{
	SCON=0X50;
	TMOD=0X20;
	PCON=0X80;
	TH1=0XF3;
	TL1=0XF3;
	ES=1;
	EA=1;
	TR1=1;
}

void UsartSend(uchar dat)
{
	SBUF = dat;
	while(!TI);
	TI=0;
}
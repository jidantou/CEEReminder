#include "display.h"
#include "intrins.h"

uchar smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};
uchar disdata[4]={0x76,0x76,0x76,0x76};

void Send595(uchar dat)
{
	uchar i;
	RC=1;
	SC=1;
	for(i=0;i<8;i++)
	{
		SE=dat>>7;
		dat<<=1;
		SC=0;
		_nop_();
		_nop_();
		SC=1;
	}
	RC=0;
	_nop_();
	_nop_();
	RC=1;
	return;
}

void Display()
{
	uchar i;
	for(i=0;i<4;i++)
	{
		switch(i)
		{
			case(0):wei_1=0;wei_2=1;wei_3=1;wei_4=1;break;
			case(1):wei_1=1;wei_2=0;wei_3=1;wei_4=1;break;
			case(2):wei_1=1;wei_2=1;wei_3=0;wei_4=1;break;
			case(3):wei_1=1;wei_2=1;wei_3=1;wei_4=0;break;
		}
		Send595(disdata[i]);
		delay(100);
		Send595(0x00);
	}
	return;
}

void delay(uchar i)
{
	while(i--);
}										   

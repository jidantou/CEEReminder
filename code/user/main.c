#include "reg52.h"
#include "ds1302.h"
#include "display.h"
#include "sumdays.h"
#include "init.h"
#include "intrins.h"

u8 mode=0,beep_set=0;
u16 second=0;

void mode0()
{
    u8 year,mouth,day;
	u16 count;
	year=((Time[6]/16)*10)+(Time[6]&0x0f);
	mouth=((Time[4]/16)*10)+(Time[4]&0x0f);
	day=((Time[3]/16)*10)+(Time[3]&0x0f);
    count=caldays(year,mouth,day);
    disdata[0]=0x00;
    disdata[1]=smgduan[count/100];
    disdata[2]=smgduan[(count%100)/10];
    disdata[3]=smgduan[(count%10)];
}

void mode1()
{
    disdata[0]=smgduan[Time[2]/16];
    disdata[1]=smgduan[Time[2]&0x0f];
    disdata[2]=smgduan[Time[1]/16];
    disdata[3]=smgduan[Time[1]&0x0f];
}

void mode2()
{
    disdata[0]=smgduan[Time[4]/16];
    disdata[1]=smgduan[Time[4]&0x0f];
    disdata[2]=smgduan[Time[3]/16];
    disdata[3]=smgduan[Time[3]&0x0f];
}

void mode3()
{
    disdata[0]=smgduan[alackh/10];
	disdata[1]=smgduan[alackh%10];
	disdata[2]=smgduan[alackm/10];
	disdata[3]=smgduan[alackm%10];
}
void init()
{
    P_SW2=0x80;
		
    CKSEL=0x00;
    XOSCCR=0x00;

    P0M0=0x00;
    P0M1=0x00;
    P1M0=0x00;
    P1M1=0x00;
    P2M0=0x00;
    P2M1=0x00;
    P3M0=0x00;
    P3M1=0x00;
    P5M0=0x00;
    P5M1=0x00;

    P_SW2=0X00;

	IT0=1;
	EX0=1;
}

void Time0Init()
{
    TMOD=0x00;
	TH0=0x3C;		//50ms
	TL0=0xB0;
	ET0=1;
	EA=1;
	//TR0=1;
}

void main()
{
    init();
	Time0Init();
    DS1302Init();
    beep=0;
    while(1)
    {
        ReadTime();
        switch(mode)
        {
            case(0):mode0();break;
            case(1):mode1();break;
            case(2):mode2();break;
            case(3):mode3();break;
        }
        Display();
		if(Time[1]==alackm&&Time[2]==alackh&&beep_set==1)
		{
			beep_set=1;
			beep=~beep;
		}
		/*if(second==60)
		{
			second=0;
			TR0=0;
			beep_set=0;
		}*/
    }
    return;
}

void time0() interrupt 1
{
    static u16 i;
	i++;
	if(i==20)
	{
		i=0;
		second++;	
	}
	/*if(second==60)
		second=0;*/
}

void int0() interrupt 0
{
	delay(1000);
	if(keymode==0)
		mode++;
	if(mode>3)
		mode=0;
}
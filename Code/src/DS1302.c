#include "global.h"
#include "DS1302.h"

// Write address and Time in DS1302
uchar code DS_WriteAdress[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
// saved in BCD code
// 2022.01.01 00:00:00
// 0:second, 1:minute, 2:hour, 3:day, 4:month, 5:week, 6:year 
uchar DS1302Time[7] = {0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x22};
uchar Time[7] = {0, 0, 0, 1, 1, 1, 22};

// Send dat to addr in DS1302
void DS1302Write(uchar addr,uchar dat)
{
	// var i for loop
	uchar i;
	
	DS_RST = 0;
	_nop_();
	DS_SCLK = 0;
	_nop_();
	DS_RST = 1;
	_nop_();
	
	// Send addr
	for (i=0; i<8; i++)
	{
		// Send from low bite to high bite
		DS_IO = addr & 0x01;
		addr >>= 1;
		// DS1302 read dat in DS_SCLK high
		DS_SCLK = 1;
		_nop_();
		DS_SCLK = 0;
		_nop_();
	}
	
	// Send dat,same as sending dat
	for (i=0; i<8; i++)
	{
		DS_IO = dat & 0x01;
		dat >>= 1;
		DS_SCLK = 1;
		_nop_();
		DS_SCLK = 0;
		_nop_();	
	}	
	
	// Reset to nomal
	DS_RST = 0;
	_nop_();
}

// Read dat in addr
uchar DS1302Read(uchar addr)
{
	// var i for loop,dat for received dat,dat1 save the value in IO
	uchar i,dat,dat1;
	
	DS_RST = 0;
	_nop_();
	DS_SCLK = 0;
	_nop_();
	DS_RST = 1;
	_nop_();

	// Send addr
	for(i=0; i<8; i++)
	{
		DS_IO = addr & 0x01;
		addr >>= 1;
		DS_SCLK = 1;
		_nop_();
		DS_SCLK = 0;
		_nop_();
	}
	// 
	_nop_();
	
	// Receive dat
	for(i=0; i<8; i++)
	{
		dat1 = DS_IO;
		dat = (dat>>1) | (dat1<<7);	// Save in val dat
		DS_SCLK = 1;
		_nop_();
		DS_SCLK = 0;
		_nop_();
	}

	DS_RST = 0;
	_nop_();
	
	// DS1302 return to normal
	DS_SCLK = 1;
	_nop_();
	DS_IO = 0;
	_nop_();
	_nop_();
	DS_IO = 1;
	
	return dat;
}

void DS1302SetTime()
{
	uchar i;
	DS1302Write(0x8E,0X00);
	for (i=0; i<7; i++)
	{
		DS1302Time[i] = UcharToBCD(Time[i]);
		DS1302Write(DS_WriteAdress[i],DS1302Time[i]);	
	}
	DS1302Write(0x8E,0x80);
}

void DS1302ReadTime()
{
	uchar i;
	for (i=0; i<7; i++)
	{
		DS1302Time[i] = DS1302Read(DS_WriteAdress[i]+1);
		Time[i] = BCDToUchar(DS1302Time[i]);
	}
}
#include "reg52.h"
#ifndef _ds1302_h_
#define	_ds1302_h_

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit T_CE=P3^7;
sbit T_SCLK=P1^1;
sbit T_IO=P1^0;

extern uchar Time[7];

void WriteDS1302(uchar addr,uchar dat);
uchar ReadDS1302(uchar addr);
void DS1302Init();
void ReadTime();

#endif
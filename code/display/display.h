#include "reg52.h"
#ifndef _display_h_
#define _display_h_

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sfr P5=0xC8;

sbit RC=P1^3;
sbit SC=P1^4;
sbit SE=P1^2;
sbit wei_1=P1^5;
sbit wei_2=P1^6;
sbit wei_3=P1^7;
sbit wei_4=P5^5;

extern uchar smgduan[17];
extern uchar disdata[4];

void Send595(uchar dat);
void Display();
void delay(uchar i);

#endif
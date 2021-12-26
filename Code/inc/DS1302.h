#ifndef _DS1302_h_
#define _DS1302_h_

#include "reg52.h"
#include "global.h"
#include "intrins.h"	//include _nop_();

//Define IO used in DS1302
sbit DS_IO=P2^0;
sbit DS_RST=P2^1;
sbit DS_SCLK=P2^2;

//Declare funtions used in DS1302
void DS1302ReadTime();
void DS1302SetTime();

#endif
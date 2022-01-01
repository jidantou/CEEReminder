#ifndef _DS1302_h_
#define _DS1302_h_

#include "reg52.h"
#include "global.h"
#include "intrins.h"	//include _nop_();

//Define IO used in DS1302
sbit DS_IO=P1 ^ 2;
sbit DS_RST=P1 ^ 0;
sbit DS_SCLK=P1 ^ 1;

//Declare funtions used in DS1302
void DS1302ReadTime();
void DS1302SetTime();

#endif
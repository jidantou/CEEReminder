#include "ds1302.h"
#include "intrins.h"

uchar code com[7]={0x81,0x83,0x85,0x87,0x89,0x8B,0x8D};
//读地址命令，写入时需-1
uchar Time[7]={0x00,0x00,0x09,0x07,0x06,0x01,0x21};
//储存顺序是秒分时日月周年
//2021年6月7日上午9:00，周一

void WriteDS1302(uchar addr,uchar dat)
{
	uchar i;
	T_CE=0;
	_nop_();
	T_SCLK=0;
	_nop_();
	T_CE=1;
	_nop_();
	for(i=0;i<8;i++)
	{
		T_IO=addr&0x01;
		_nop_();
		addr>>=1;
		T_SCLK=1;
		_nop_();
		T_SCLK=0;
		_nop_();
	}
	for(i=0;i<8;i++)
	{
		T_IO=dat&0x01;
		_nop_();
		dat>>=1;
		T_SCLK=1;
		_nop_();
		T_SCLK=0;
		_nop_();
	}
	T_CE=0;
	_nop_();
	return;
}
uchar ReadDS1302(uchar addr)
{
	uchar i,dat,dat0;
	T_CE=0;
	_nop_();
	T_CE=1;
	_nop_();
	for(i=0;i<8;i++)
	{
		T_IO=addr&0x01;
		_nop_();
		addr>>=1;
		T_SCLK=1;
		_nop_();
		T_SCLK=0;
		_nop_();
	}
	for(i=0;i<8;i++)
	{
		dat0=T_IO;
		dat=(dat>>1)|(dat0<<7);
		_nop_();
		T_SCLK=1;
		_nop_();
		T_SCLK=0;
		_nop_();
	}
	T_CE=0;
	_nop_();
	return dat;
}
void DS1302Init()
{
	uchar i;
	WriteDS1302(0x8E,0x00);
	for(i=0;i<7;i++)
	{
		WriteDS1302(com[i]-1,Time[i]);
	}
	WriteDS1302(0x90,0xA6);
	WriteDS1302(0x8E,0x80);
	return;
}
void ReadTime()
{
	uchar i=0;
	while(i<7)
	{
		Time[i]=ReadDS1302(com[i]);
		i++;
	}
	return;
}
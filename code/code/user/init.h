#ifndef _init_
#define _init_

#define CKSEL (*(unsigned char volatile xdata *)0xFE00)
#define CLKDIV (*(unsigned char volatile xdata *)0xFE01)
#define HIRCCR (*(unsigned char volatile xdata *)0xFE02)
#define XOSCCR (*(unsigned char volatile xdata *)0xFE03)
#define IRC32KCR (*(unsigned char volatile xdata *)0xFE04)

#define alackh 0x08
#define alackm 0x00

sfr P_SW2=0XBA;
sfr IRTRIM=0X9F;

sfr P0M0=0x94;
sfr P0M1=0x93;
sfr P1M0=0x92;
sfr P1M1=0x91;
sfr P2M0=0x96;
sfr P2M1=0x95;
sfr P3M0=0xb2;
sfr P3M1=0xb1;
sfr P4M0=0xb4;
sfr P4M1=0xb3;
sfr P5M0=0xca;
sfr P5M1=0xc9;

typedef unsigned char u8;
typedef unsigned int u16;

sbit beep=P3^5;
sbit keymode=P3^2;
sbit key1=P3^3;
sbit key2=P3^6;

//void mode0();
//void mode1();
//void mode2();
//void mode3();
//void init();
//void Time0Init();

#endif
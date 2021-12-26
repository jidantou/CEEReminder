//Display.h
#ifndef _Display_h_
#define _Display_h_

sbit SCL=P1^0;
sbit SDA=P1^1;

#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

// Function list
void OLED_Init();

void OLED_Cls();
void OLED_Fill(uchar x, y, witch, height, bmp_dat);
void OLED_Show(uchar x, y, width, height,uchar *dat, uchar mode);

#endif
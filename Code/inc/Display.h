//Display.h
#ifndef _Display_h_
#define _Display_h_

sbit SCL=P2 ^ 0;
sbit SDA=P2 ^ 1;

#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

// Function list
void OLED_Init();

void OLED_Cls();
void OLED_Fill(uchar x1, y1, x2, y2, mode);
void OLED_Show(uchar x, y, width, height,uchar *dat, uchar mode);

#endif
#ifndef _GUI_H_
#define _GUI_H_

void OLED_Cls();  // in Display.c

void GUI_Start();
void GUI_CEE();
void GUI_Time(uchar mode); 
void GUI_Date(uchar mode);
void GUI_CountDown(uchar N, mode);
void GUI_Memu0();
void GUI_Memu1();
void GUI_SetCEE();

#endif
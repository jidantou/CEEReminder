#ifndef _global_h_
#define _global_h_

#include "reg52.h"
#include "intrins.h"

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned char u8;
typedef unsigned int u16;

// Global var
extern uchar Time[7];	// in DS1302.c
extern uchar CEEDAY[3]; // in golbal.c
extern uchar CURSOR;	// in global.c
extern uchar CountDown[2][2]; // in global.c
extern uchar CountPause[2];  // in global.c
/* ShowMode:
 0: GUI_CEE();
 1: GUI_Time(0);
 2:	GUI_Date(0);
 3:	GUI_CountDown(0, 0);
 4:	GUI_CountDown(1, 0);
 5:	GUI_Memu0();
 6:	GUI_Memu1();
 7: GUI_SetCEE();
 8: GUI_Time(1);
 9: GUI_Date(1);
 10: GUI_CountDown(0, 1);
 11: GUI_CountDown(1, 1);
*/
extern uchar ShowMode;  // in global.c
extern uchar KeySign;  // in global.c

// Funcion list
void delay(u16 i);
void delay_long(u16 i);
uint Caldays(uchar year1,uchar mouth1,uchar day1);	// in sumdays.c
uchar BCDToUchar(uchar value);
uchar UcharToBCD(uchar dat);

// DEBUG
void UsartInit();
void UsartSend(uchar dat);


#endif
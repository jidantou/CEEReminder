//GUI.c
#include "global.h"
#include "GUI.h"
#include "Display.h"
#include "FontLib.h"

const uchar code Points[8] = {0xC0, 0xC0, 0x03, 0x03, 0xC0, 0xC0, 0x03, 0x03};

const uchar Pause[6] = {0x3F, 0x3F, 0x3F, 0xFC, 0xFC, 0xFC};

void GUI_Start()
{
	uchar i;
	
	for(i = 0; i < 9; i++)
		OLED_Show((8 + 8 * i), 2, 8, 2, Asc8x16[10 + i], 0);
	OLED_Show(80, 2, 16, 2,Bmp16x16, 0);
	OLED_Show(96, 2, 8, 2, Asc8x16[2], 0);
	OLED_Show(104, 2, 8, 2, Asc8x16[0], 0);
	OLED_Show(112, 2, 8, 2, Asc8x16[2], 0);
	OLED_Show(120, 2, 8, 2, Asc8x16[2], 0);
	for(i = 0; i < 6; i++)
		OLED_Show(16 + 16 * i, 4, 16, 2, Ch16x16[i], 0);
}

void GUI_CEE()
{
	uchar i;
	uint days;	

	for(i = 0; i < 6; i++)
		OLED_Show(16 + 16 * i, 1, 16, 2, Ch16x16[6 + i], 0);
	days = Caldays(Time[6], Time[4], Time[3]);
	OLED_Show(32, 3, 16, 4, Num16x32[days / 100], 0);
	OLED_Show(48, 3, 16, 4, Num16x32[(days / 10) % 10], 0);
	OLED_Show(64, 3, 16, 4, Num16x32[days % 10], 0);
	OLED_Show(80, 5, 16, 2, Ch16x16[12], 0);
}

void GUI_SetCEE()
{
	OLED_Show(16, 1, 16, 2, Ch16x16[24], 0);
	OLED_Show(32, 1, 16, 2, Ch16x16[25], 0);
	OLED_Show(48, 1, 16, 2, Ch16x16[8], 0);
	OLED_Show(64, 1, 16, 2, Ch16x16[9], 0);
	OLED_Show(80, 1, 16, 2, Ch16x16[15], 0);
	OLED_Show(96, 1, 16, 2, Ch16x16[27], 0);

	OLED_Show(8, 3, 8, 2, Asc8x16[2], (CURSOR >> 0) & 0x01);
	OLED_Show(16, 3, 8, 2, Asc8x16[0], (CURSOR >> 0) & 0x01);
	OLED_Show(24, 3, 8, 2, Asc8x16[CEEDAY[0] / 10], (CURSOR >> 0) & 0x01);
	OLED_Show(32, 3, 8, 2, Asc8x16[CEEDAY[0] % 10], (CURSOR >> 0) & 0x01);

	OLED_Show(40, 3, 16, 2, Ch16x16[13], 0);

	OLED_Show(56, 3, 8, 2, Asc8x16[CEEDAY[1] / 10], (CURSOR >> 1) & 0x01);
	OLED_Show(64, 3, 8, 2, Asc8x16[CEEDAY[1] % 10], (CURSOR >> 1) & 0x01);

	OLED_Show(72, 3, 16, 2, Ch16x16[14], 0);

	OLED_Show(88, 3, 8, 2, Asc8x16[CEEDAY[2] / 10], (CURSOR >> 2) & 0x01);
	OLED_Show(96, 3, 8, 2, Asc8x16[CEEDAY[2] % 10], (CURSOR >> 2) & 0x01);

	OLED_Show(104, 3, 16, 2, Ch16x16[15], 0);

	OLED_Show(48, 5, 16, 2, Ch16x16[19], (CURSOR >> 3) & 0x01);
	OLED_Show(64, 5, 16, 2, Ch16x16[20], (CURSOR >> 3) & 0x01);
}															

// mode: 0 for show, 1 for set
void GUI_Time(uchar mode)
{
	OLED_Show(63, 2, 2, 4, Points, 0);

	OLED_Show(27, 2, 16, 4, Num16x32[Time[2] / 10], mode * ((CURSOR >> 0) & 0x01));
	OLED_Show(43, 2, 16, 4, Num16x32[Time[2] % 10], mode * ((CURSOR >> 0) & 0x01));
	OLED_Show(69, 2, 16, 4, Num16x32[Time[1] / 10], mode * ((CURSOR >> 1) & 0x01));
	OLED_Show(85, 2, 16, 4, Num16x32[Time[1] % 10], mode * ((CURSOR >> 2) & 0x01));

	if(mode == 1)
	{
		OLED_Show(32, 0, 16, 2, Ch16x16[24], 0);
		OLED_Show(48, 0, 16, 2, Ch16x16[25], 0);
		OLED_Show(64, 0, 16, 2, Ch16x16[23], 0);
		OLED_Show(80, 0, 16, 2, Ch16x16[26], 0);

		OLED_Show(48, 6, 16, 2, Ch16x16[19], (CURSOR >> 3) & 0x01);
		OLED_Show(64, 6, 16, 2, Ch16x16[20], (CURSOR >> 3) & 0x01);
	}
}

void GUI_Date(uchar mode)
{	
	OLED_Show(40, 2, 8, 2, Asc8x16[2], mode * ((CURSOR >> 1) & 0x01));
	OLED_Show(48, 2, 8, 2, Asc8x16[0], mode * ((CURSOR >> 1) & 0x01));	
	OLED_Show(56, 2, 8, 2, Asc8x16[Time[7] / 10], mode * ((CURSOR >> 0) & 0x01));	
	OLED_Show(64, 2, 8, 2, Asc8x16[Time[7] % 10], mode * ((CURSOR >> 0) & 0x01));
	OLED_Show(72, 2, 16, 2, Ch16x16[13], 0);

	OLED_Show(32, 4, 8, 2, Asc8x16[Time[5] % 10], mode * ((CURSOR >> 1) & 0x01));
	OLED_Show(40, 4, 8, 2, Asc8x16[Time[5] % 10], mode * ((CURSOR >> 1) & 0x01));
	OLED_Show(48, 4, 16, 2, Ch16x16[14], 0);
				
	OLED_Show(64, 4, 8, 2, Asc8x16[Time[4] % 10], mode * ((CURSOR >> 2) & 0x01));
	OLED_Show(72, 4, 8, 2, Asc8x16[Time[4] % 10], mode * ((CURSOR >> 2) & 0x01));
	OLED_Show(80, 4, 16, 2, Ch16x16[15], 0);

	if(mode == 1)
	{
		OLED_Show(32, 0, 16, 2, Ch16x16[24], 0);
		OLED_Show(48, 0, 16, 2, Ch16x16[25], 0);
		OLED_Show(64, 0, 16, 2, Ch16x16[23], 0);
		OLED_Show(80, 0, 16, 2, Ch16x16[26], 0);

		OLED_Show(48, 6, 16, 2, Ch16x16[19], ((CURSOR >> 3) & 0x01));
		OLED_Show(64, 6, 16, 2, Ch16x16[20], ((CURSOR >> 3) & 0x01));
	}
}

void GUI_CountDown(uchar N, mode)
{
	 OLED_Show(32, 0, 16, 2, Ch16x16[21], 0);
	 OLED_Show(48, 0, 16, 2, Ch16x16[22], 0);
	 OLED_Show(64, 0, 16, 2, Ch16x16[23], 0);
	 OLED_Show(80, 0, 8, 2, Asc8x16[N + 1], 0);

	 OLED_Show(63, 2, 2, 4, Points, 0);

	 OLED_Show(27, 2, 16, 4, Num16x32[CountDown[N][0] / 10], mode * ((CURSOR >> 0) & 0x01));
	 OLED_Show(43, 2, 16, 4, Num16x32[CountDown[N][0] % 10], mode * ((CURSOR >> 0) & 0x01));
	 OLED_Show(69, 2, 16, 4, Num16x32[CountDown[N][1] / 10], mode * ((CURSOR >> 1) & 0x01));
	 OLED_Show(85, 2, 16, 4, Num16x32[CountDown[N][1] % 10], mode * ((CURSOR >> 1) & 0x01));

	 if(mode == 1)
	 {
		 OLED_Show(24, 6, 16, 2, Ch16x16[30], (CURSOR >> 2) & 0x01);
		 OLED_Show(40, 6, 16, 2, Ch16x16[31], (CURSOR >> 2) & 0x01);
	
		 OLED_Show(72, 6, 16, 2, Ch16x16[19], (CURSOR >> 3) & 0x01);
		 OLED_Show(88, 6, 16, 2, Ch16x16[20], (CURSOR >> 3) & 0x01);
	}

	if(CountPause[N] == 0x01 && mode == 0)
	{
		OLED_Show(59, 6, 3, 2, Pause, 0);
		OLED_Show(66, 6, 3, 2, Pause, 0);
	}
}

void GUI_Memu0()
{
	uchar i;

	for(i = 0; i < 4; i++)
	{
		OLED_Show(8, i * 2, 16, 2, Ch16x16[24], (CURSOR >> i) & 0x01);
		OLED_Show(24, i * 2, 16, 2, Ch16x16[25], (CURSOR >> i) & 0x01);
	}

	OLED_Show(40, 0, 16, 2, Ch16x16[8], (CURSOR >> 0) & 0x01);
	OLED_Show(56, 0, 16, 2, Ch16x16[9], (CURSOR >> 0) & 0x01);
	OLED_Show(72, 0, 16, 2, Ch16x16[15], (CURSOR >> 0) & 0x01);
	OLED_Show(88, 0, 16, 2, Ch16x16[27], (CURSOR >> 0) & 0x01);

	OLED_Show(40, 2, 16, 2, Ch16x16[23], (CURSOR >> 1) & 0x01);
	OLED_Show(56, 2, 16, 2, Ch16x16[26], (CURSOR >> 1) & 0x01);

	OLED_Show(40, 4, 16, 2, Ch16x16[15], (CURSOR >> 2) & 0x01);
	OLED_Show(56, 4, 16, 2, Ch16x16[27], (CURSOR >> 2) & 0x01);
		
	OLED_Show(40, 6, 16, 2, Ch16x16[21], (CURSOR >> 3) & 0x01);
	OLED_Show(56, 6, 16, 2, Ch16x16[22], (CURSOR >> 3) & 0x01);
	OLED_Show(72, 6, 16, 2, Ch16x16[23], (CURSOR >> 3) & 0x01);
	OLED_Show(88, 6, 8, 2, Asc8x16[1], (CURSOR >> 3) & 0x01);

	switch(CURSOR)
	{
		case 1:
			OLED_Fill(104, 0, 127, 1, 0xFF);
			break;
		case 2:
			OLED_Fill(72, 2, 127, 3, 0xFF);
			break;
		case 4:
			OLED_Fill(72, 4, 127, 5, 0xFF);
			break;
		case 8:
			OLED_Fill(96, 6, 127, 7, 0xFF);
			break; 
	}
}

void GUI_Memu1()
{
	OLED_Show(8, 0, 16, 2, Ch16x16[24], (CURSOR >> 0) & 0x01);
	OLED_Show(24, 0, 16, 2, Ch16x16[25], (CURSOR >> 0) & 0x01);
	OLED_Show(40, 0, 16, 2, Ch16x16[21], (CURSOR >> 0) & 0x01);
	OLED_Show(56, 0, 16, 2, Ch16x16[22], (CURSOR >> 0) & 0x01);
	OLED_Show(72, 0, 16, 2, Ch16x16[23], (CURSOR >> 0) & 0x01);
	OLED_Show(88, 0, 8, 2, Asc8x16[2], (CURSOR >> 0) & 0x01);

	OLED_Show(8, 2, 16, 2, Ch16x16[19], (CURSOR >> 1) & 0x01);
	OLED_Show(24, 2, 16, 2, Ch16x16[20], (CURSOR >> 1) & 0x01);

	switch(CURSOR)
	{
		case 1:
			OLED_Fill(96, 0, 127, 1, 0xFF);
			break;
		case 2:
			OLED_Fill(40, 2, 127, 3, 0xFF);
			break;
	}
}
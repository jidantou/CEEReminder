// Process.c
#include "global.h"
#include "Process.h"
#include "GUI.h"
#include "DS1302.h"

uchar MonthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// debug
uint debug = 10;

void Process()
{
	if(((CEEDAY[0] % 4 == 0) && (CEEDAY[0] % 100 != 0)) || (CEEDAY[0] % 400 == 0))
		MonthDay[1] = 29;
	else MonthDay[1] = 28;
}

void Count0Pro()
{
	if(CountDown[0][0] == 0 && CountDown[0][1] == 0)
	{
		CountPause[0] = 1;
		return;
	}	
	if(CountPause[0] == 0)
	{
		if(CountTime[0][0] < Time[2])
			CountDown[0][0] =24 + CountTime[0][0] - Time[2];
		else CountDown[0][0] = CountTime[0][0] - Time[2];
		
		if(CountTime[0][1] < Time[1])
		{
			CountDown[0][1] =60 + CountTime[0][1] - Time[1];
			CountDown[0][0]--;
		}
		else CountDown[0][1] = CountTime[0][1] - Time[1];		
	}

}

void Count1Pro()
{
	if(CountDown[1][0] == 0 && CountDown[1][1] == 0)
	{
		CountPause[1] = 1;
		return;
	}
	
	if(CountPause[1] == 0)
	{
		if(CountTime[1][0] < Time[2])
			CountDown[1][0] =24 + CountTime[1][0] - Time[2];
		else CountDown[1][0] = CountTime[1][0] - Time[2];
		
		if(CountTime[1][1] < Time[1])
		{
			CountDown[1][1] =60 + CountTime[1][1] - Time[1];
			CountDown[1][0]--;
		}
		else CountDown[1][1] = CountTime[1][1] - Time[1];		
	}
}

// Short for KeyProcess
void KeyPro()
{
	uchar temp, count;
	
	if(CURSOR == 0x01)
		temp = 0;
	else if(CURSOR == 0x02)
		temp = 1;
	else if(CURSOR == 0x04)
		temp = 2;
	else temp = 3;

	if((ShowMode & 0x7F) == 3 || (ShowMode & 0x7F) == 10)
		count = 0;
	else if((ShowMode & 0x7F) == 4 || (ShowMode & 0x7F) == 11)
		count = 1;

	switch(ShowMode & 0x7F)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:	
		if(KeySign & 0x01)		// Down
		{
			KeySign &= 0xFE;
			ShowMode++;
			ShowMode |= 0x80;
			if((ShowMode & 0x7F) >= 5)
				ShowMode = 0x80;
		}
		if(KeySign & 0x02)		// Up
		{
			KeySign &= 0xFD;
			if((ShowMode & 0x7F) == 0)
				ShowMode =0x84;
			else ShowMode--;
			ShowMode |= 0x80;
		}
		if(KeySign & 0x04)		// Memu
		{
			KeySign &= 0xFB;
			ShowMode = 0x85;
		}
		if(KeySign & 0x08)		// Enter
		{
			KeySign &= 0xF7;
			if(CountPause[count] == 1)
			{
				CountPause[count] = 0;
				CountTime[count][0] = CountDown[count][0];
				CountTime[count][1] = CountDown[count][1];

				CountTime[count][1] += Time[1];
				if(CountTime[count][1] > 59)
				{
					CountTime[count][1] -= 60;
					CountTime[count][0]++;
				}
				CountTime[count][0] += Time[2];
				if(CountTime[count][0] > 23)
					CountTime[count][0] -= 24;
			}
			else CountPause[count] = 1;
		}
		break;
	case 5:
		if(KeySign & 0x01)		// Down
		{
			KeySign &= 0xFE;
			CURSOR <<= 1;
			if(CURSOR == 0x10)
			{
				ShowMode = 0x86;
				CURSOR = 0x01;
			}
			ShowMode |= 0x80;
		}
		if(KeySign & 0x02)		// Up
		{
			KeySign &= 0xFD;
			if(CURSOR == 0x01)
			{
				ShowMode =0x86;
				CURSOR = 0x02;
			}
			else CURSOR >>= 1;
			ShowMode |= 0x80;
		}
		if(KeySign & 0x04)		// Memu
		{
			KeySign &= 0xFB;
			ShowMode = 0x80;
			debug = ShowMode;

			CURSOR = 0x01;
		}
		if(KeySign & 0x08)		// Enter
		{
			KeySign &= 0xF7;
			if(CURSOR == 0x01)
				ShowMode = 0x87;
			else if (CURSOR == 0x02)
				ShowMode = 0x88;
			else if(CURSOR == 0x04)
				ShowMode = 0x89;
			else if(CURSOR == 0x08)
				ShowMode = 0x8A;
			CURSOR = 0x01;
		}
		break;
	case 6:
		if(KeySign & 0x01)		// Down
		{
			KeySign &= 0xFE;
            CURSOR <<= 1;
            if(CURSOR == 0x04)
            {
                ShowMode = 0x85;
                CURSOR = 0x01;
            }
		}
		if(KeySign & 0x02)		// Up
		{
            KeySign &=0xFD;
            if(CURSOR ==1)
            {
                ShowMode =0x85;
                CURSOR = 0x08;
            }
            else CURSOR >>= 1;
		}
		if(KeySign & 0x04)		// Memu
		{
            KeySign &= 0xFB;
            ShowMode = 0x80;
            CURSOR = 0x01;
		}
		if(KeySign & 0x08)		// Enter
		{
            KeySign &= 0xF7;
            if(CURSOR == 0x01)
                ShowMode = 0x8B;
            else ShowMode = 0x80;
            CURSOR = 0x01;
		}
		break;
	case 7:
		if(KeySign & 0x01)		// Down
		{
			KeySign &= 0xFE;
			if(CURSOR == 0x01)
				if(CEEDAY[0] == 0)
					CEEDAY[0] = 99;
				else CEEDAY[0]--;
			else if(CURSOR == 0x02)
				if(CEEDAY[1] == 1)
					CEEDAY[1] = 12;
				else CEEDAY[1]--;
			else if(CURSOR == 0x04)
				if(CEEDAY[2] == 1)
					CEEDAY[2] = MonthDay[CEEDAY[1]];
				else CEEDAY[2]--;				
		}
		if(KeySign & 0x02)		// Up
		{
            KeySign &=0xFD;
			if(CURSOR == 0x01)
			{
				CEEDAY[0]++;
				if(CEEDAY[0] == 100)
					CEEDAY[0] = 0;
			}
			else if(CURSOR == 0x02)
			{
				CEEDAY[1]++;
				if(CEEDAY[1] == 13)
					CEEDAY[1] = 1;
			}
			else if(CURSOR == 0x04)
			{
				CEEDAY[2]++;
				if(CEEDAY[2] == (MonthDay[CEEDAY[1]] + 1))
					 CEEDAY[2] = 1;
			}
		}
		if(KeySign & 0x04)		// Memu
		{
            KeySign &= 0xFB;
			CURSOR <<= 1;
			if(CURSOR == 0x10)
				CURSOR = 0x01;
		}
		if(KeySign & 0x08)		// Enter
		{
            KeySign &= 0xF7;
			if(CURSOR == 0x08)
			{
				ShowMode = 0x85;
				CURSOR = 0x01;
			}
		}
		break;
	case 8:
		if(KeySign & 0x01)		// Down
		{
			KeySign &= 0xFE;
			if(CURSOR == 0x01)
				if(Time[2] == 0)
					Time[2] = 23;
				else Time[2]--;
			else if(CURSOR == 0x02)
				if((Time[1] / 10) == 0)
					Time[1] = 50 + Time[1] % 10;
				else Time[1] -= 10;
			else if(CURSOR == 0x04)
				if((Time[1] % 10) == 0)
					Time[1] = 9 + (Time[1] / 10) * 10;
				else Time[1]--;				
		}
		if(KeySign & 0x02)		// Up
		{
            KeySign &= 0xFD;
			if(CURSOR == 0x01)
			{	
				if(++Time[2] == 24)
					Time[2] = 0;
			}
			else if(CURSOR == 0x02)
			{
				Time[1] += 10;
				if((Time[1] / 10) == 6)
					Time[1] = Time[1] % 10;
			}
			else if(CURSOR == 0x04)
			{
				if(Time[1] % 10 == 9)
					 Time[1] -= 9;
				else  Time[1]++;
			}
		}
		if(KeySign & 0x04)		// Memu
		{
            KeySign &= 0xFB;
			CURSOR <<= 1;
			if(CURSOR == 0x10)
				CURSOR = 0x01;
		}
		if(KeySign & 0x08)		// Enter
		{
            KeySign &= 0xF7;
			if(CURSOR == 0x08)
			{
				CURSOR = 0x01;
				ShowMode = 0x85;
			}
		}
		DS1302SetTime();
		break;
	case 9:
		if(KeySign & 0x01)		// Down
		{
			KeySign &= 0xFE;
			if(CURSOR == 0x01)
			{
				if(Time[6] == 0)
					Time[6] = 99;
				else Time[6]--;
			}
			else if(CURSOR == 0x02)
			{				
				if(Time[4] == 1)
				{
					Time[4] = 12;
				}
				else Time[4]--;
			}
			else if(CURSOR == 0x04)
			{
				if(Time[3] == 1)
				{
					Time[3] = MonthDay[Time[4] - 1];
				}
				else Time[3]--;
			}
		}
		if(KeySign & 0x02)		// Up
		{
            KeySign &=0xFD;
			if(CURSOR == 0x01)
			{
				if(++Time[6] == 100)
					Time[6] = 0;
			}
			else if(CURSOR == 0x02)
			{
				if(++Time[4] == 13)
					Time[4] = 1;
			}
			else if(CURSOR == 0x04)
			{
				if(++Time[3] == (MonthDay[Time[4]] + 1))
					Time[3] = 1;
			}
		}
		if(KeySign & 0x04)		// Memu
		{
            KeySign &= 0xFB;
			CURSOR <<= 1;
			if(CURSOR == 0x10)
				CURSOR = 0x01;
		}
		if(KeySign & 0x08)		// Enter
		{
            KeySign &= 0xF7;
			if(CURSOR == 0x08)
			{
				CURSOR = 0x01;
				ShowMode = 0x85;
			}
		}
		DS1302SetTime();
		break;
	case 10:
	case 11:
		if(KeySign & 0x01)		// Down
		{
			KeySign &= 0xFE;
			if(CURSOR == 0x01)
			{
				if(CountDown[count][0] == 0)
					CountDown[count][0] = 23;
				else CountDown[count][0]--;
			}
			else if(CURSOR == 0x02)
			{
				if(CountDown[count][1] == 0)
					CountDown[count][1] = 59;
				else CountDown[count][1]--;
			}
		}
		if(KeySign & 0x02)		// Up
		{
            KeySign &=0xFD;
			if(CURSOR == 0x01)
			{
				if(++CountDown[count][0] == 24)
					CountDown[count][0] = 0;
			}
			else if(CURSOR == 0x02)
			{
				if(++CountDown[count][1] == 60)
					CountDown[count][1] = 0;
			}
		}
		if(KeySign & 0x04)		// Memu
		{
            KeySign &= 0xFB;
			CURSOR <<= 1;
			if(CURSOR == 0x10)
				CURSOR = 0x01;
		}
		if(KeySign & 0x08)		// Enter
		{
            KeySign &= 0xF7;
			if(CURSOR == 0x04)
			{
				CountDown[count][0] = 1;
				CountDown[count][1] = 30;
			}
			if(CURSOR == 0x08)
			{
				CURSOR = 0x01;
				ShowMode = 0x85;
			}
		}
		break;
	}
}

void InterruptInit()
{
	// INT0
	IT0 = 1;
	EX0 = 1;
	// INT1
	IT1 = 1;
	EX1 = 1;
	// Timer0
	TMOD|=0X01;
	TH0=0XFC;  // 1ms
	TL0=0X18;
	ET0=1;

	// All interrupt
	EA=1;

}
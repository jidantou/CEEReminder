#include "global.h"
#include "Display.h"
//#include "FontLib.h"

// Delay function in Display.c
void delay12864(uint z)
{
	uint y;
	for(; z > 0; z--)
		for(y = 110; y > 0; y--);
}

// Write one byte by IIC
void Write_IIC_Byte(uchar IIC_Byte)
{
	uchar i;
	for(i = 0; i <8; i++)
	{
		if(IIC_Byte & 0x80)
			SDA = 1;
		else
			SDA = 0;
		SCL = 1;
		SCL = 0;
		IIC_Byte <<= 1;
	}
	SDA = 1;
	SCL = 1;
	SCL = 0;
}

// Write data to OLED
void OLED_WrDat(uchar IIC_Data)
{
	//IIC start
	SCL = 1;		
  SDA = 1;
  SDA = 0;
	SCL = 0;
	
	Write_IIC_Byte(0x78);
	Write_IIC_Byte(0x40);	//write data
	Write_IIC_Byte(IIC_Data);
	
	//IIC stop
	SCL = 0;
  SDA = 0;
  SCL = 1;
  SDA = 1;
}

// Write command to OLED
void OLED_WrCmd(uchar IIC_Command)
{
	// IIC start
	SCL = 1;
  SDA = 1;
  SDA = 0;
  SCL = 0;
	
	Write_IIC_Byte(0x78);	//Slave address,SA0=0
	Write_IIC_Byte(0x00);	//write command
	Write_IIC_Byte(IIC_Command);
	
	// IIC stop
	SCL = 0;
  SDA = 0;
  SCL = 1;
  SDA = 1;
}

// Set start position
void OLED_Set_Pos(uchar x, uchar y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0) >> 4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
} 

// OLED full screen
void OLED_Fill(uchar x1, y1, x2, y2, bmp_dat) 
{
	uchar row;
		
	for(; y1 <= y2; y1++)
	{
		OLED_Set_Pos(x1, y1);
		for(row = x1; row <= x2; row++)
			OLED_WrDat(bmp_dat);
	}
}

// OLED reset
void OLED_Cls()
{
	uchar y, x;
	for(y = 0; y < 8; y++)	// y for page
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)	// x for row
			OLED_WrDat(0);
	}
}

// OLED init
void OLED_Init()
{
	delay12864(500);	//Can't be deleted
	OLED_WrCmd(0xae);	//--turn off oled panel
	OLED_WrCmd(0x00);	//---set low column address
	OLED_WrCmd(0x10);	//---set high column address
	OLED_WrCmd(0x40);	//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);	//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);	//--Set SEG/Column Mapping     0xa0???? 0xa1??
	OLED_WrCmd(0xc8);	//Set COM/Row Scan Direction   0xc0???? 0xc8??
	OLED_WrCmd(0xa6);	//--set normal display
	OLED_WrCmd(0xa8);	//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);	//--1/64 duty
	OLED_WrCmd(0xd3);	//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);	//-not offset
	OLED_WrCmd(0xd5);	//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);	//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);	//--set pre-charge period
	OLED_WrCmd(0xf1);	//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);	//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);	//--set vcomh
	OLED_WrCmd(0x40);	//Set VCOM Deselect Level
	OLED_WrCmd(0x20);	//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);
	OLED_WrCmd(0x8d);	//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);	//--set(0x10) disable
	OLED_WrCmd(0xa4);	// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);	// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);	//--turn on oled panel

	OLED_Cls();	//Clear screen
	OLED_Set_Pos(0,0);
}
//y,height for page
void OLED_Show(uchar x, y, width, height, uchar *dat, uchar mode)
{
	uchar row, line;
	for(line = 0; line < height; line++)
	{
		OLED_Set_Pos(x,y + line);
		for(row = 0; row < width; row++)
			if(mode == 1)
				OLED_WrDat(dat[row + width * line] ^ 0xFF);
			else
				OLED_WrDat(dat[row + width * line]);
	}		
}

/*
// OLED show 6x8 word
void OLED_P6x8Str(uchar x, y, uchar ch[])
{
	uchar c = 0, i = 0, j=0;
	while (ch[j] != '\0')
	{
		c = ch[j]-32;
		if(x > 126)
		{
			x = 0;
			y++;
		}
		OLED_Set_Pos(x,y);
		for(i = 0; i < 6; i++)
			OLED_WrDat(F6x8[c][i]);
		x += 6;
		j++;
	}
}


//OLED show 8x16 word
void OLED_ASC8x16(uchar x, y, uchar N)
{
	uchar row;	

	OLED_Set_Pos(x,y);
	for(row = 0; row < 8; row++)
		OLED_WrDat(ASC8x16[N][row]);

	OLED_Set_Pos(x,y+1);
	for(row = 0; row < 8; row++)
		OLED_WrDat(ASC8x16[N][row + 8]);
}

//OLED show Chinese character size in 16x16
//x for row, y for page, N for serial number in Ch16x16[N][32] 
void OLED_Ch16x16(uchar x, y, N)
{
	uchar row;
	
	OLED_Set_Pos(x, y);
	for(row = 0; row < 16; row++)
		OLED_WrDat(Ch16x16[N][row]);

	OLED_Set_Pos(x, y + 1);
	for(row = 0; row < 16; row++)
		OLED_WrDat(Ch16x16[N][row + 16]);
}

void OLED_Num16x32(uchar x, uchar y, uchar N)
{
	uchar row;
	uchar i = 0;
	
	for(i = 0; i < 4; i++)
	{
		OLED_Set_Pos(x, y + i);
		for(row = 0; row < 16; row++)
			OLED_WrDat(Num16x32[N][row + 16 * i]);
	}
}


//OLED show bmp
void Draw_BMP(uchar x0, y0,x1, y1,uchar BMP[])
{
	uint j = 0;
	uchar x, y;

  if(y1%8 == 0)
		y=y1 / 8;      
  else
		y=y1 /8 + 1;
	for(y = y0; y < y1; y++)
	{
		OLED_Set_Pos(x0,y);
    for(x = x0; x < x1; x++)
	    {      
	    	OLED_WrDat(BMP[j++]);
	    }
	}
}
*/

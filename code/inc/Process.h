// Process.h
#ifndef _Process_h_
#define _Process_h_

sbit key0 = P3 ^ 2;  // Enter
sbit key1 = P3 ^ 3;	 // Memu
sbit key2 = P3 ^ 6;  // Up
sbit key3 = P3 ^ 7;  // Down

// Function list
void KeyPro();
void Process();
void InterruptInit();
void Count0Pro();
void Count1Pro();

#endif
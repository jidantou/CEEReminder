// Process.h
#ifndef _Process_h_
#define _Process_h_

sbit key0 = P3 ^ 2;  // Up
sbit key1 = P3 ^ 3;	 // Down
sbit key2 = P2 ^ 5;  // Memu
sbit key3 = P2 ^ 4;  // Enter

// Function list
void KeyPro();
void Process();
void InterruptInit();

#endif
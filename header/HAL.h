#ifndef _HAL_H_
#define _HAL_H_

#include  "../header/BSP.h"    		    // private library - BSP layer
#include  "../header/Application.h"     // private library - APP layer
#include  <msp430g2553.h>               // MSP430x2xx
//#include  <msp430xG46x.h>             // MSP430x4xx 

extern enum FSMstate state;   // global variable
extern enum SYSmode lpm_mode; // global variable

// System
extern void sysConfig(void);
extern void enterLPM(unsigned char);

// LEDs
extern void print2LEDs(unsigned char);
extern void clrLEDs(void);
extern void toggleLEDs(char);
extern void setLEDs(char);
extern void incLEDs(char);

// Interrupts
extern void enable_interrupts();
extern void disable_interrupts();

// LCD
extern void lcd_cmd(unsigned char);
extern void lcd_data(unsigned char);
extern void lcd_init();
extern void lcd_strobe();
extern void LCDErase(void);

// Delays
extern void DelayMs(unsigned int);
extern void DelayUs(unsigned int);
extern void delay(unsigned int);

// Timers
extern void ResetTimer();
extern void TIMERdelay(int);



extern unsigned char readSWs(void);
#endif

#ifndef _API_H_
#define _API_H_

#include  "../header/HAL.h"     // private library - HAL layer

extern void lcd_puts(const char * s);
extern void int_to_str(char *str, unsigned int number);

#endif

#ifndef _API_H_
#define _API_H_

#include  "../header/HAL.h"     // private library - HAL layer

extern void lcd_puts(const char * s);
extern void int_to_str(char *str, unsigned int number);
extern void sleep(void);
extern void RGB_blink(void);
extern void count_up(void);
extern void count_down(void);
extern void get_X(void);
extern void potentiometer(void);
extern void clear_all(void);
extern void show_menu(void);
extern int str_to_int( char volatile *str);

#endif

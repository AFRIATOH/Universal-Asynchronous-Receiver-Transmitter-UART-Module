#include  "../header/API.h"    		// private library - API layer
#include  "../header/HAL.h"     // private library - HAL layer


//******************************************************************
// write a string of chars to the LCD
//******************************************************************
void lcd_puts(const char * s){
  
	while(*s)
	    lcd_data(*s++);

}

//******************************************************************
//function - intger to string
//******************************************************************
void int_to_str(char *str, unsigned int number){
   long tmp = number, Strlen = 0;
   int lenth = 0;

   while(tmp){
       Strlen++;
       tmp /= 10;
   }
   int k;
   for(k = Strlen - 1; k >= 0; k--){
       str[k] = (number % 10) + '0';
       number /= 10;
   }

   lenth = Strlen;
   str[lenth] = '\0';
   
}

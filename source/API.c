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

//******************************************************************
//state1
//******************************************************************
void RGB_blink(void){

}

//******************************************************************
//state2
//******************************************************************
void count_up(void){

}

//******************************************************************
//state3
//******************************************************************
void count_down(void){

}

//******************************************************************
//state4
//******************************************************************
void get_X(void){

}

//******************************************************************
//state5
//******************************************************************
void potentiometer(void){

}

//******************************************************************
//state6
//******************************************************************
void clear_all(void){

}

//******************************************************************
//state7
//******************************************************************
void show_menu(void){

}

//******************************************************************
//state8
//******************************************************************

            // real time task
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
   int length = 0;

   while(tmp){
       Strlen++;
       tmp /= 10;
   }
   int k;
   for(k = Strlen - 1; k >= 0; k--){
       str[k] = (number % 10) + '0';
       number /= 10;
   }

   length = Strlen;
   str[length] = '\0';
   
}

void print_num(int num){
    // char num_1 = 0x30+(num%10);
    // char num_2 = 0x30+(num%100);
    // char num_3 = 0x30+(num%1000);
    // char num_4 = 0x30+(num%10000);
    // char num_5 = 0x30+(num%100000);
    // char num_6 = 0x30+(num%1000000);
    // if(num < 10){
    //     LCDErase();
    //     lcd_data(ones);
    //     lcd_puts(" notes");
    // }
    // else {
    //     char tens = 0x30+(num/10);
    //     LCDErase();
    //     lcd_data(tens);
    //     lcd_data(ones);
    //     lcd_puts(" notes");
    // }
    if(num < 10){
        char pr[1];
        int_to_str(pr, num);
        lcd_puts(pr);
    }
    else if(num < 100){
        char pr[2];
        int_to_str(pr, num);
        lcd_puts(pr);
    }
    else if(num < 1000){
        char pr[3];
        int_to_str(pr, num);
        lcd_puts(pr);
    }
    else if(num < 10000){
        char pr[4];
        int_to_str(pr, num);
        lcd_puts(pr);
    }
    else if(num < 100000){
        char pr[5];
        int_to_str(pr, num);
        lcd_puts(pr);
    }
    else if(num < 1000000){
        char pr[6];
        int_to_str(pr, num);
        lcd_puts(pr);
    }

}

//******************************************************************
//state0
//******************************************************************
void sleep(void){
    RGB_clear;
    lcd_clear();
    menu_tx = 1;
    UCA0CTL1 &= ~UCSWRST;
    IE2 |= UCA0TXIE;
    __bis_SR_register(LPM0_bits + GIE); 
}

//******************************************************************
//state1
//******************************************************************
void RGB_blink(void){
    RGB_clear;
    lcd_clear();
    while(state == state1){
        RGBPort = 0x01;
        delay_x(X_delay);
        RGBPort = 0x02;
        delay_x(X_delay);
        RGBPort = 0x04;
        delay_x(X_delay);
    }
}

//******************************************************************
//state2
//******************************************************************
void count_up(void){
    RGB_clear;
    while(state == state2){
        lcd_clear();
        print_num(count_up_val);
        count_up_val += 1;
        delay_x(X_delay);
    }
}

//******************************************************************
//state3
//******************************************************************
void count_down(void){
    RGB_clear;
    while(state == state3){
        lcd_clear();
        print_num(count_down_val);
        count_down_val -= 1;
        delay_x(X_delay);
    }
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
    // RGB_clear;
    // lcd_clear();
    // count_up_val = 0;
    // count_down_val = 65535;
    //state = state0;
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
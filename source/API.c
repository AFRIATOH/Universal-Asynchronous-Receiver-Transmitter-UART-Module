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

int str_to_int( char volatile *str)
{
    int i,res = 0;
    for (i = 0; str[i] != '\0'; ++i) {
        if (str[i]> '9' || str[i]<'0')
            return -1;
        res = res * 10 + str[i] - '0';
    }

    return res;
}

void to_string(char *str, unsigned int number){

    int size = 0;
    long tmp = number;
    long len = 0;

    // Find the size of the intPart by repeatedly dividing by 10
    while(tmp){
        len++;
        tmp /= 10;
    }

    // Print out the numbers in reverse
    int j;
    for(j = len - 1; j >= 0; j--){
        str[j] = (number % 10) + '0';
        number /= 10;
    }
    size += len;
    str[size] = '\0';
}

void print_num(int num){
    if(num == 0){
        lcd_data('0');
    }
    else if(num < 10){
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
    // tx = 1;
    // UCA0CTL1 &= ~UCSWRST;
    // IE2 |= UCA0TXIE;
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
        delay_x(X_delay);
        count_up_val += 1;
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
    __bis_SR_register(LPM0_bits+GIE);
}

//******************************************************************
//state5
//******************************************************************
void potentiometer(){
    ADC10CTL0 = ADC10SHT_0 + ADC10IE;
    ADC10CTL0 |= ADC10ON;
    ADC10CTL0 &= ~ENC;
    while(ADC10CTL1 & ADC10BUSY);
    ADC10CTL0 |= ENC + ADC10SC;
    __bis_SR_register(CPUOFF + GIE);
    __no_operation();                       // For debugger
    ADC10CTL0 &= ~ADC10ON;
    to_string(potentiometer_val,ADC10MEM);
    UCA0CTL1 &= ~UCSWRST;
    IE2 |= UCA0TXIE;
}
//******************************************************************
//state6
//******************************************************************
void clear_all(void){
    count_up_val = 0;
    count_down_val = 65535;
    state = state0;
}

//******************************************************************
//state7
//******************************************************************
void show_menu(void){
    RGB_clear;
    lcd_clear();
    tx = 1;
    UCA0CTL1 &= ~UCSWRST;
    IE2 |= UCA0TXIE;
    __bis_SR_register(LPM0_bits + GIE);
}

//******************************************************************
//state8
//******************************************************************



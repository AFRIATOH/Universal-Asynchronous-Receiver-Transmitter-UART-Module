#include  "../header/HAL.h"     // private library - HAL layer
#include  "../header/API.h"    		// private library - API layer

unsigned int i,j;
int menu_tx = 1;
const char MENU[] = "\n"
					"-----------------------Menu-------------------------\n"
					"1. Blink RGB LED, color by color with delay of X[ms]\n"
					"2. Count up onto LCD screen with delay of X[ms]\n"
					"3. Count down onto LCD screen with delay of X[ms]\n"
					"4. Get delay time X[ms]\n"
					"5. Potentiometer 3-digit value [v]\n"
					"6. Clear LCD screen\n"
					"7. Show menu\n"
                    "8. Sleep\n"
					"---------------------------------------------------\r";
					
//--------------------------------------------------------------------
//             System Configuration  
//--------------------------------------------------------------------
void sysConfig(void)
{ 
	UARTconfig();
	ADCconfig();
	RGBconfig();
  	lcd_init();
	//GPIOconfig();
	TIMERconfig();
}

//---------------------------------------------------------------------
//            Polling based Delay function
//---------------------------------------------------------------------
void delay(unsigned int t){  // t[msec]
	volatile unsigned int i;
	for(i=t; i>0; i--);
}

//---------------------------------------------------------------------
//            Delay function
//---------------------------------------------------------------------
void delay_x(unsigned int t){  // t[msec]
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = t*130;
  __bis_SR_register(LPM0_bits + GIE);
}

//---------------------------------------------------------------------
//            Enter from LPM0 mode
//---------------------------------------------------------------------
void enterLPM(unsigned char LPM_level){
	if (LPM_level == 0x00) 
	  _BIS_SR(LPM0_bits);     /* Enter Low Power Mode 0 */
        else if(LPM_level == 0x01) 
	  _BIS_SR(LPM1_bits);     /* Enter Low Power Mode 1 */
        else if(LPM_level == 0x02) 
	  _BIS_SR(LPM2_bits);     /* Enter Low Power Mode 2 */
	else if(LPM_level == 0x03) 
	  _BIS_SR(LPM3_bits);     /* Enter Low Power Mode 3 */
        else if(LPM_level == 0x04) 
	  _BIS_SR(LPM4_bits);     /* Enter Low Power Mode 4 */
}

//*********************************************************************
//            UART RX Interrupt Service Rotine
//*********************************************************************

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  if (state != state4){
	    if (UCA0RXBUF - 48 == 1)                          // '1' received?
		{
			state = state1;
			__bic_SR_register_on_exit(LPM0_bits + GIE);
		}
		else if (UCA0RXBUF == '2')                     // '2' received?
		{
			state = state2;
			__bic_SR_register_on_exit(LPM0_bits + GIE);
		}
		else if (UCA0RXBUF == '3')                     // '3' received?
		{
			state = state3;
			__bic_SR_register_on_exit(LPM0_bits + GIE);
		}
		else if (UCA0RXBUF == '5')                     // '5' received?
		{
			state = state5;
			__bic_SR_register_on_exit(LPM0_bits + GIE);
		}
		else if (UCA0RXBUF == '6')                     // '6' received?
		{
			state = state6;
			__bic_SR_register_on_exit(LPM0_bits + GIE);
		}
		else if (UCA0RXBUF == '7')                     // '7' received?
		{
			state = state7;
			__bic_SR_register_on_exit(LPM0_bits + GIE);
		}
		else if (UCA0RXBUF == '8')                     // '8' received?
		{
			state = state0;
			__bic_SR_register_on_exit(LPM0_bits + GIE);
		}
		else if (UCA0RXBUF == '9')                     // '9' received?
		{
			state = state8;
			__bic_SR_register_on_exit(LPM0_bits + GIE);
		}
			else if (UCA0RXBUF == '4')                     // '4' received?
		{
			//change X
		}
  }
  else {

  }

}

//*********************************************************************
//            UART TX Interrupt Service Rotine
//*********************************************************************

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)

{           		
	if(state == state5){
		// TxBuffer = POT[i++];
		// if (i == sizeof POT -1){					     // TX over?
		// 	i = 0; 
		// 	IE2 &= ~UCA0TXIE;        					 // Disable USCI_A0 TX interrupt
		// 	IE2 |= UCA0RXIE;                 			 // Enable USCI_A0 RX interrupt	
		// 	state = 7;
			menu_tx = 0;
            // }
	}
	else if(menu_tx){
        UCA0TXBUF = MENU[i++];
        if (i == sizeof MENU - 1){						 // TX over?
                i = 0; 
                IE2 &= ~UCA0TXIE;                		 // Disable USCI_A0 TX interrupt
                IE2 |= UCA0RXIE;                 		 // Enable USCI_A0 RX interrupt	
        }			
	}
	else{
	  IE2 &= ~UCA0TXIE;    
	}
}

//------------------------------------------------------------------
//           Port1 Interrupt Service Rotine 
//------------------------------------------------------------------

// void _buttonDebounceDelay(int button){
//     volatile unsigned int i;
//     for(i = 1000; i > 0; i--);                     //delay, button debounce
// 	while(!(P1IN & button)); 		   // wait of release the button
//     for(i = 1000; i > 0; i--);                     //delay, button debounce
//     P1IFG &= ~button;       	   // manual clear of p1.button
// }

// #pragma vector=PORT1_VECTOR
// __interrupt void PORT1_ISR(void){
// 	if(P1IFG & 0x10){
// 		_buttonDebounceDelay(0x10);
// 		menu_tx = 1;
// 		UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
// 		IE2 |= UCA0TXIE;                          // Enable USCI_A0 TX interrupt
// 	}
// }

//------------------------------------------------------------------
//           Timer A0 Interrupt Service Rotine 
//------------------------------------------------------------------

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void){
	CCTL0 &= ~CCIE;                        	     // CCR0 interrupt enabled
	__bic_SR_register_on_exit(LPM0_bits + GIE);  // Exit LPM0 on return to main
}

//******************************************************************
// send a command to the LCD
//******************************************************************
void lcd_cmd(unsigned char c){

    LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

    if (LCD_MODE == FOURBIT_MODE)
    {
        LCD_DATA_WRITE &= ~OUTPUT_DATA;// clear bits before new write
                LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
        lcd_strobe();
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
            LCD_DATA_WRITE |= (c & (0x0F)) << LCD_DATA_OFFSET;
        lcd_strobe();
    }
    else
    {
        LCD_DATA_WRITE = c;
        lcd_strobe();
    }
}
//---------------------------------------------------------------------
//                         LCD clear and erase 
//---------------------------------------------------------------------
void LCDErase(void)
{
        LCD_RS(0);
        lcd_clear();
        lcd_home();
        LCD_RS(1);
}

//******************************************************************
// send data to the LCD
//******************************************************************
void lcd_data(unsigned char c)
{

    LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

    LCD_DATA_WRITE &= ~OUTPUT_DATA;

    LCD_RS(1);
    if (LCD_MODE == FOURBIT_MODE)
    {
            LCD_DATA_WRITE &= ~OUTPUT_DATA;
                LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
        lcd_strobe();
                LCD_DATA_WRITE &= (0xF0 << LCD_DATA_OFFSET) | (0xF0 >> 8 - LCD_DATA_OFFSET);
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
        LCD_DATA_WRITE |= (c & 0x0F) << LCD_DATA_OFFSET;
        lcd_strobe();
    }
    else
    {
        LCD_DATA_WRITE = c;
        lcd_strobe();
    }

    LCD_RS(0);
}

//******************************************************************
// initialize the LCD
//******************************************************************
void lcd_init(){
        LCD_DATA_SEL &= ~0xF0 ;
        LCD_DATA_DIR |= 0xF0 ;
        LCD_CTRL_SEL &= ~0xE0 ;
	char init_value;

	if (LCD_MODE == FOURBIT_MODE) init_value = 0x3 << LCD_DATA_OFFSET;
        else init_value = 0x3F;

	LCD_RS_DIR(OUTPUT_PIN);
	LCD_EN_DIR(OUTPUT_PIN);
	LCD_RW_DIR(OUTPUT_PIN);
    LCD_DATA_DIR |= OUTPUT_DATA;
    LCD_RS(0);
	LCD_EN(0);
	LCD_RW(0);

	DelayMs(15);
    LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();
	DelayMs(5);
    LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();
	DelayUs(200);
    LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();

	if (LCD_MODE == FOURBIT_MODE){
		LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h
        LCD_DATA_WRITE &= ~OUTPUT_DATA;
		LCD_DATA_WRITE |= 0x2 << LCD_DATA_OFFSET; // Set 4-bit mode
		lcd_strobe();
		lcd_cmd(0x28); // Function Set
	}
    else lcd_cmd(0x3C); // 8bit,two lines,5x10 dots

	lcd_cmd(0xF); //Display On, Cursor On, Cursor Blink
	lcd_cmd(0x1); //Display Clear
	lcd_cmd(0x6); //Entry Mode
	lcd_cmd(0x80); //Initialize DDRAM address to zero
    lcd_cmd(0x01);
    lcd_cmd(0x02);
}

//******************************************************************
// Delay usec functions
//******************************************************************
void DelayUs(unsigned int cnt){

	unsigned char i;
        for(i=cnt ; i>0 ; i--) asm(" nop"); // tha command asm("nop") takes raphly 1usec

}

//******************************************************************
// Delay msec functions
//******************************************************************
void DelayMs(unsigned int cnt){

	unsigned char i;
        for(i=cnt ; i>0 ; i--) DelayUs(1000); // tha command asm("nop") takes raphly 1usec

}

//******************************************************************
// lcd strobe functions
//******************************************************************
void lcd_strobe(){
  LCD_EN(1);
  asm(" nop");
  asm(" nop");
  LCD_EN(0);
}

//---------------------------------------------------------------------
//            Enable interrupts
//---------------------------------------------------------------------
void enable_interrupts(){
  _BIS_SR(GIE);
}
//---------------------------------------------------------------------
//            Disable interrupts
//---------------------------------------------------------------------
void disable_interrupts(){
  _BIC_SR(GIE);
}


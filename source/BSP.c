#include  "../header/API.h"    		    // private library - API layer
#include  "../header/Application.h"     // private library - APP layer
#include  "../header/BSP.h"             // private library - BSP layer


//-----------------------------------------------------------------------------  
//           GPIO congiguration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
 
  _BIS_SR(GIE);                     // enable interrupts globally
}                             

//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
void TIMERconfig(void){

    TACCR0=0xFFFF;
    TACTL=TASSEL_2+MC_1;// SET TIMER TO WORK WITH MASTERCLOCK AND TO COUNT UNTILL THE VALUE OF TBCL
    TACCTL0=CCIE;

}

//------------------------------------------------------------------------------------- 
//            ADC congiguration 
//-------------------------------------------------------------------------------------
void ADCconfig(void){
	
	//write here ADC congiguration code
}   

//------------------------------------------------------------------------------------- 
//           UART congiguration 
//-------------------------------------------------------------------------------------
voit UARTconfig(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  if (CALBC1_1MHZ==0xFF)					// If calibration constant erased
  {											
    while(1);                               // do not load, trap CPU!!	
  }
  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  
//   P2DIR = 0xFF;                             // All P2.x outputs
//   P2OUT = 0;                                // All P2.x reset
  P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  P1DIR |= RXLED + TXLED;
  P1OUT &= 0x00;
  
  UCA0CTL1 |= UCSSEL_2;                     // CLK = SMCLK
  UCA0BR0 = 104;                           // 
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = UCBRS0;               // 
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM3 w/ int until Byte RXed
}
//******************************************************************
// Delay usec functions
//******************************************************************
void DelayyUs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) asm(" nop"); // tha command asm("nop") takes raphly 1usec
	
}
//******************************************************************
// Delay msec functions
//******************************************************************
void DelayyMs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) DelayUs(1000); // tha command asm("nop") takes raphly 1usec
	
}
//******************************************************************


#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
    //write here TimerB congiguration code
}

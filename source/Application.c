#include  "../header/API.h"    		    // private library - API layer
#include  "../header/Application.h"    	// private library - APP layer

enum FSMstate state;
enum SYSmode lpm_mode;

extern int X_delay = 500;

void main(void){
  
  sysConfig();
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET

  while(1)
  {
    switch(state)
    {
      case state0:
        enterLPM(lpm_mode);
      break;
                  
      case state1: 
            // RGB blink with delay of X
      break; 
  
      case state2:
            // count up on LCD with delay of X
      break;

      case state3:
            // count down on LCD with delay of X
      break;

      case state4: 
            // set X
      break; 
  
      case state5:
            // potentiometer
      break;

      case state6:
            // clear LCD
      break;

      case state7: 
            // show menu
      break; 
    }
  }
}

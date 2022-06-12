#include  "../header/API.h"    		    // private library - API layer
#include  "../header/Application.h"    	// private library - APP layer

enum FSMstate state;
enum SYSmode lpm_mode;

extern int X_delay = 500;
extern int count_up_val = 0;
extern int count_down_val = 65535;

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
            RGB_blink(); // RGB blink with delay of X
      break; 
  
      case state2:
            count_up(); // count up on LCD with delay of X
      break;

      case state3:
            count_down(); // count down on LCD with delay of X
      break;

      case state4: 
            get_X(); // set X using
      break; 
  
      case state5:
            potentiometer(); // potentiometer
      break;

      case state6:
            clear_all(); // clear LCD
      break;

      case state7: 
            show_menu(); // show menu on PC screen
      break; 
    }
  }
}

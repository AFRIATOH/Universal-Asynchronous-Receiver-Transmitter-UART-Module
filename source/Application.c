#include  "../header/API.h"    		    // private library - API layer
#include  "../header/Application.h"    	// private library - APP layer

enum FSMstate state;
enum SYSmode lpm_mode;

extern int LCD_cursor = 0;

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

      break; 
  
      case state2:

      break;

     case state3:

     break;
    }
  }
}


//test
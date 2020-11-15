#include <msp430.h>
#include "stateMachines.h"
#include "lcdutils.h"

int master = 0;                 /* master state set automatically to 0 */
int substate = 0;               /* substate set automatically to 0 */
int x = 500;                    /* x set to 0 */

void color_advance()   		   /* switch between different dimming modes */
{
  secCount = 0;
    fontFgColor2 = (fontFgColor == COLOR_RED) ? COLOR_RED : COLOR_WHITE;
    fontFgColor = (fontFgColor == COLOR_RED) ? COLOR_WHITE : COLOR_RED;
    redrawScreen = 1;
}

/*
void ambulance_advance(int stateA)
{
  switch(stateA){
  case 0:
    buzzer_set_period(2000000/2500);  /* set buzzer 
      green_on_all();                   /* 2 lines set lights 
      red_off();
      break;
  case 1:
    buzzer_set_period(2000000/500);    set buzzer 
      red_on_all();                      set leds
      green_off();
      break;
  }
}
*/




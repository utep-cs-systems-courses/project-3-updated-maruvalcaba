#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "buzzer.h"

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_RED;
u_int fontFgColor2 = COLOR_WHITE;
int secCount = 0;

void wdt_c_handler()
{
  secCount ++;
  if (secCount == 250) {		/* once/sec */
    color_advance();
  }
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  buzzer_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      drawString5x7(20,20, "hello", fontFgColor, COLOR_BLACK);
      u_char offc = 30;
      u_char offr = 30;
      for(u_char r = 0; r < 10; r++){
	for(u_char c = 0; c <= r; c++){            
	  drawPixel(offc-c, offr+r, fontFgColor);
	  drawPixel(offc+c, offr+r, fontFgColor);
	  drawPixel(offc-c, offr+19-r, fontFgColor2);  /* this also makes a diamond */
	  drawPixel(offc+c, offr+19-r, fontFgColor2);
	}
      }
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    




#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "buzzer.h"
#include "switches.h"

#define LED_GREEN BIT6             // P1.6
#define LED_RED BIT0

short redrawScreen3 = 0;
char substateLed = 0;
short redrawScreen = 0;
short redrawScreen2 = 1;
u_int fontFgColor = COLOR_RED;
u_int fontFgColor2 = COLOR_WHITE;
int secCount = 0;
char seconds = 0;
char state_changed = 0;
void wdt_c_handler()
{
  switch(master){
  case 0:
    secCount ++;
    if(secCount == 10){
      buzzer_set_period(0);
    }
    if (secCount == 25 && seconds <= 7) {		/* once/sec */
      seconds++;
      secCount = 0;
      redrawScreen = 1;
      redrawScreen2 = 1;
    }
    if(secCount == 250 && seconds > 7){
      secCount = 0;
      redrawScreen = 1;
      color_advance();
    }
    break;
  case 1:
    secCount++;
    switch(movestate){
    case 0:
    case 1:
      if(secCount == 5){
	redrawScreen = 1;
	secCount = 0;
      }
      break;
    case 3:
      break;
    }
    break;
  case 2:
    seconds++;
    if(seconds == 125){
      seconds = 0;
      substateLed++;
    }
    if(substateLed == 5){
      substateLed = 0;
    }
    and_sr(~0x8);	              /**< GIE (disable interrupts) */
    state_changed = state_advance(substateLed);
    or_sr(0x8);	              /**< GIE (enable interrupts) */
    break;
  }
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */
  P1DIR |= LED_RED;
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  buzzer_init();
  switch_init();

  clearScreen(COLOR_BLACK);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */ 
  
  while (1) {			/* forever */
    if (redrawScreen) {
      switch(master){
      case 0:
	redrawScreen = 0;
	if(redrawScreen3){
	  clearScreen(COLOR_BLACK);
	  seconds = 1;
	  secCount = 0;
	  redrawScreen3 = 0;
	}
	else if(redrawScreen2){
	  redrawScreen2 = 0;
	  main_menu_advance();
	}
	else{
	  // drawDiamond(screenWidth/2, screenHeight/2-25, fontFgColor);
	  drawString8x12(screenWidth/2-36, screenHeight/2-50,"Welcome!", fontFgColor, COLOR_BLACK);
	  drawString5x7(screenWidth/2-48, screenHeight/2-25,"Press S1 to load", fontFgColor, COLOR_BLACK);
	  drawString5x7(screenWidth/2-45, screenHeight/2-10,"Press S2 or S3", fontFgColor, COLOR_BLACK);
	  drawString5x7(screenWidth/2-27, screenHeight/2,"to reload", fontFgColor, COLOR_BLACK);

	  drawString5x7(screenWidth/2-45, screenHeight/2+15,"Press S4 to load", fontFgColor, COLOR_BLACK);
	  drawString5x7(screenWidth/2-32, screenHeight/2+25,"dimming demo", fontFgColor, COLOR_BLACK);
	  
	  drawHouse(screenWidth/2, screenHeight/2+50, fontFgColor, fontFgColor2);

	}
	break;
      case 1:
	redrawScreen = 0;
	switch(movestate){
	case 0:
	case 1:
	  and_sr(~0x8);
	  motion_advance();
	  or_sr(0x8);
	  break;
	case 3:
	  if(redrawScreen3){
	    clearScreen(COLOR_WHITE);
	    seconds = 0;
	    secCount = 0;
	    redrawScreen3 = 0;
	  }
	  drawString5x7(screenWidth/2-48, screenHeight/2-25,"Press S2 to move", COLOR_BLACK, COLOR_WHITE);
	  drawString5x7(screenWidth/2-30, screenHeight/2-15,"to the left", COLOR_BLACK, COLOR_WHITE);
	  drawString5x7(screenWidth/2-48, screenHeight/2,"Press S3 to move", COLOR_BLACK, COLOR_WHITE);
	  drawString5x7(screenWidth/2-35, screenHeight/2+10,"to the right", COLOR_BLACK, COLOR_WHITE);
	  break;
	}
	break;
      case 2:	
	break;
      }
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    secCount = 0;
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}


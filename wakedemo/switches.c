#include <msp430.h>
#include "switches.h"
#include "stateMachines.h"
#include "lcddraw.h"
#include "lcdutils.h"
#include "buzzer.h"


char switch_state_down, switch_state_changed, blink_count, blink_count2, seconds; /* effectively boolean */
int master, x;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  return p2val;
}

void 
switch_init()			/* setup switches */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  master = 0;
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switch(master){
  case 0:
    if((p2val & SW1) == 0){       /* if SW1 is the button pressed down */
      seconds = 0;                /* next few lines update variables */
      secCount = 0;
      movestate = 3;
      clearScreen(COLOR_WHITE);
      master = 1;
      redrawScreen = 1;
      buzzer_set_period(0);
    }
    else if((p2val & SW4) == 0){       /* if SW1 is the button pressed down */
      seconds = 0;                /* next few lines update variables */
      secCount = 0;
      master = 2;
    }
    else{                         /* else, SW4 is being pressed down or null state */
      master = 0;                 /* next few lines update variables */
      secCount = 0;
      seconds = 0;
      char *mainString = "Welcome!";
      string = mainString;
      redrawScreen = 0;
      redrawScreen2 = 1;
      clearScreen(COLOR_BLACK);
      rcolS = screenWidth/2-36;
    }
    break;
  case 1:
    if((p2val & SW1) == 0){       /* if SW1 is the button pressed down */
      movestate = 3;
      master = 1;
      clearScreen(COLOR_WHITE);
      seconds = 0;                /* next few lines update variables */
      secCount = 0;
      redrawScreen = 1;
      buzzer_set_period(0);
    }
    else if((p2val & SW2) == 0){
      seconds = 0;                /* next few lines update variables */
      secCount = 0;
      movestate = 1;
      master = 1;
      buzzer_set_period(0);
    }
    else if((p2val & SW3) == 0){
      seconds = 0;                /* next few lines update variables */
      secCount = 0;
      movestate = 0;
      master = 1;
      buzzer_set_period(0);
    }
    else{                         /* else, SW4 is being pressed down or null state */
      master = 0;                 /* next few lines update variables */
      secCount = 0;
      seconds = 0;
      char *mainString = "Welcome!";
      string = mainString;
      redrawScreen = 0;
      redrawScreen2 = 1;
      clearScreen(COLOR_BLACK);
      rcolS = screenWidth/2-36;
    }
    break;
  case 2:
    clearScreen(COLOR_BLACK);
    master = 0;                 /* next few lines update variables */
    secCount = 0;
    seconds = 0;
    char *mainString = "Welcome!";
    string = mainString;
    redrawScreen = 0;
    redrawScreen2 = 1;
    rcolS = screenWidth/2-36;
    break;
  }
  switch_state_changed = 1;
}

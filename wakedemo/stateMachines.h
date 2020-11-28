#ifndef stateMachine_included
#define stateMachine_included

extern int master;

extern int movestate;

extern int colorState;

extern int substate;

extern unsigned char rcolS;

extern int x;               /* frequency */

extern char blink_count2;   /* secondary blink count */
extern char seconds;

extern char blink_count;

extern char *string;

void color_advance();

void main_menu_advance();

void motion_advance();

void red_off();

void green_off();

void both_on();

char state_advance(char substateLed);

char red_on_all();

char toggle_red();

char red_33();

char red_66();

char red_25();

char green_on_all();

char toggle_green();

char green_33();

char green_66();

char green_25();


void ambulance_advance(int stateA);
#endif // included

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

void ambulance_advance(int stateA);
#endif // included

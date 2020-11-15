#ifndef stateMachine_included
#define stateMachine_included

extern int master;

extern int substate;

extern int x;               /* frequency */

extern char blink_count2;   /* secondary blink count */
extern char seconds;

extern char blink_count;

void color_advance();

void ambulance_advance(int stateA);
#endif // included

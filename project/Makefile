# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:funtoy.elf

#additional rules for files
funtoy.elf: ${COMMON_OBJECTS} main.o stateMachines.o state_advance.o drawRight.o buzzer.o p2_interrupt_handler.o switches.o drawFunctions.o wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: funtoy.elf
	msp430loader.sh $^

main.o: stateMachines.h drawFunctions.h main.h

stateMachines.o: stateMachines.h

switches.o: switches.h 

state_advance.o: stateMachines.h

clean:
	rm -f *.o *.elf

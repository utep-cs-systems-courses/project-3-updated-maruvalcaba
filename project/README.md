## Description
This program utilizes the 4 buttons on the green board, SW1 - SW4, to switch
between different states of the toy. The different states may also have their
own functionality with the buttons. Pressing the different buttons will have
a different toy function be enabled.

## How to use

(1) To compile the program, use the command 'make' to compile all the
necessary files. Then, use the command 'make load' and this should load it
onto the MSP430.

(2) When the device is powered on and loaded, it will automatically load you
onto the Main Menu screen. This screen will write "Welcome!" in a type writer
fashion and then wait for input.

(3) If you press the different switches they will have different
outcomes.

## While on the Main Menu
- Pressing SW1 will move you to the loaded 'game', which will display some
instructions and wait for input.

- Pressing SW2 and SW3 will reload the Main Menu.

- Pressing SW4 will take the toy to the dimming demo as requested by Ricardo.

## While on the 'game'
- Pressing SW1 will move you to the loaded 'game' again, reloading the white
screen waiting for input again.

- Pressing SW2 will move the box to the left with sound based on position.

- Pressing SW3 will move the box to the right with sound based on position.

- Pressing SW4 will go back to the Main Menu

## While on the buzzer demo
- Pressing SW3 will take you back to the Main Menu.

- Pressing anything else will have no effect in this state.

## To clean up

To clean up, use the 'make clean' command.

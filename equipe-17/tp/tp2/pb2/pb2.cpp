/********************************************************
/* Copyright (c) 2022 
/*
/* All rights reserved to use, copy, modify, and distribute
/* Authors: Evan BLANC 2079808 and Ahmed ZGHAL 2068299 - TEAM 17
/* INF1900
/* Polytecnhique Montréal ENGINEERING SCHOOl, Canada, Qc
*********************************************************/


/*
+----------------------------------------------------------------------+
|                                                                      |
| Pb 2                                                                 |
+----------------------------------------------------------------------+
|                                                                      |
| STATES : RED, AMBER, GREEN, OFF                                      |
+------------------------------+-------------------+-------------------+
|        INPUT                 |     NEXT STATE    |  CURRENT STATE    |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Button interrupt(press)      | AMBER             | RED               |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Button interrupt(release)    | GREEN             | AMBER             |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Button interrupt(press)      | RED               | GREEN             |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Button interrupt(release)    | OFF               | RED               |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Button interrupt(press)      | GREEN             | OFF               |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Button interrupt(release)    | RED               | GREEN             |
+------------------------------+-------------------+-------------------+
*/

#include <avr/io.h>
#define F_CPU 8000000U
#include <util/delay.h>
#include <stdint.h>

const int DELAY_GREEN_LED = 2000;
const int DELAY_DEBOUNCE = 10;
const int DELAY_GREEN_AMBER_LED = 2;
const int DELAY_RED_AMBER_LED = 14 ;

bool redButtonPressed = false;
bool greenButtonPressed = false;


/**
 * @brief if the button is pressed for the specified delay time, the function return true, false if not
 * 
 * @return true 
 * @return false 
 */
bool isButtonPressed() {
    if (PIND & 0x04) {
        _delay_ms(DELAY_DEBOUNCE);
        return PIND & 0x04; 
    }
    return false;
}


/**
 * @brief Set the pin PA1 to HIGH wich turns on the green LED
 * 
 */
const void turnLedOnGreen() {
    PORTA = (1 << PA1);
}


/**
 * @brief Set the pin PA0 to HIGH wich turns on the red LED
 * 
 */
const void turnLedOnRed() {
    PORTA = (1 << PA0);
}


/**
 * @brief The Amber color is a combination of red and green, with a certain delay to make it look better.
 * 
 */
void turnLedOnAmber() {
    turnLedOnGreen();
    _delay_ms(DELAY_GREEN_AMBER_LED);
    turnLedOnRed();
    _delay_ms(DELAY_RED_AMBER_LED);
}


/**
 * @brief Set the pin PA1 to LOW wich turns on the green LED
 * 
 */
const void turnLedOff(){
    PORTA &= ~((1<<PA1) | (1<<PA0)); // on s'assure d'avoir 0 à pin 1 et pin 0 puis on applique le masque
}


/**
 * @brief The 4 states of the machine, init is OFF linked to the outpout "led is off", then RED linked to the output "LED is red",
 * then GREEN linked to the output "LED is green", then the final state wich is AMBER, linked to the output "LED is amber"
 */
enum class State {
    OFF,
    RED,
    GREEN,
    AMBER
};


/**
 * @brief We used a "swich case" structure to represent the state machine.
 * It allows us to start with initial state, then depending on the currentState, the right action will be executed,
 * and the next state will become the current state, then back to initial state.
 * 
 * @return int 
 */
int main() {
    DDRA |= 0xff;
    DDRD |= 0x00;

    State currentState = State::RED;

    while (true) {
        switch (currentState) {

            case State::OFF:
                turnLedOff();
                if (isButtonPressed()) {
                    currentState = State::GREEN;
                }

                greenButtonPressed = true;
                break;

            case State::RED:
                if (!redButtonPressed) {
                    turnLedOnRed(); 
                    if (isButtonPressed()) {
                        currentState = State::AMBER; 
                    }         
                }
                
                else  {    
                    if (isButtonPressed()) {
                        while (isButtonPressed()) {
                            turnLedOnRed();                   
                        }
                        currentState = State::OFF; 
                        redButtonPressed = false; 
                    }
                }
                break;

            case State::GREEN:
                turnLedOnGreen();
                if ((!greenButtonPressed) && (isButtonPressed())) {
                    redButtonPressed = true;
                    currentState = State::RED; 
                }
                
                else if ((greenButtonPressed) && (!isButtonPressed())) {           
                    redButtonPressed = false;
                    greenButtonPressed = false;
                    currentState = State::RED;
                }
                break;
                
            case State::AMBER:
                while (isButtonPressed()) { 
                    turnLedOnAmber(); 
                }
                currentState = State::GREEN;
                break;
        }
    }
}
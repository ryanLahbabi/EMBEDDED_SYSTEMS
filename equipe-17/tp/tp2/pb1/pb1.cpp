/********************************************************
/* Copyright (c) 2022 
/*
/* All rights reserved to use, copy, modify, and distribute
/* Authors: Evan BLANC 2079808 and Ahmed ZGHAL 2068299 - TEAM 17
/* INF1900
/* Polytecnhique Montréal ENGINEERING SCHOOl, Canada, Qc
*********************************************************/

/*
+-------------------------------------------------------------+
|                                                             |
| Pb 1 
+-------------------------------------------------------------+
|                                                             |
| STATES : OFF, INTERM1, INTERM2, GEEN 
+---------------------+-------------------+-------------------+
|        INPUT        |     NEXT STATE     |  CURRENT STATE   |
+---------------------+-------------------+-------------------+
|                     |                   |                   |
| Button interrupt    |    INTERM1        |      OFF          |
+---------------------+-------------------+-------------------+
|                     |                   |                   |
| Button interrupt    |    INTERM2        |     INTERM1       |
+---------------------+-------------------+-------------------+
|                     |                   |                   |
| Button interrupt    |    GREEN          |     INTERM2       |
+---------------------+-------------------+-------------------+
|                     |                   |                   |
| Button interrupt    |    OFF            |     GREEN         |
+---------------------+-------------------+-------------------+
*/

#include <avr/io.h>
#define F_CPU 8000000U
#include <util/delay.h>
#include <stdint.h>

const int DELAY_GREEN_LED = 2000;
const int DELAY_DEBOUNCE = 10;

/**
 * @brief if the button is pressed for the specified delay time, the function return true, false if not
 * 
 * @return true 
 * @return false 
 */
bool isButtonPressed() {    
    if (PIND & 0x04) 
    {
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
    PORTA |= 1 << PA1;
}

/**
 * @brief Set the pin PA1 to LOW wich turns on the green LED
 * 
 */
const void turnLedOff() {
    PORTA &= ((1<<PA1) & (1<<PA0)); // on s'assure d'avoir 0 à pin 1 et pin 0 puis on applique le masque
}

/**
 * @brief The 4 states of the machine, init is OFF linked to the outpout "LED is off", then 2 intermediate states
 * because the button needs to be pressed 2 times without any impact on the LED,
 * then the final state wich is GREEN, linked to the output "LED is green"
 */
enum class State {
    OFF,
    INTERM1,
    INTERM2,
    GREEN
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
    DDRD |= 0x00; // PEUT ETRE UN & A LA PLACE ?!?

    State currentState = State::OFF;

    
    while (true) {
        switch (currentState) {

            case State::OFF:

                turnLedOff();
                while (isButtonPressed()) {
                    currentState = State::INTERM1;
                }
                break;

            case State::INTERM1:

                turnLedOff();
                while (isButtonPressed()) {
                    currentState = State::INTERM2;
                }
                break;

            case State::INTERM2 :

                turnLedOff();
                while (isButtonPressed()) {
                    currentState = State::GREEN;
                }
                break;

            case State::GREEN:
                turnLedOnGreen();
                _delay_ms(DELAY_GREEN_LED);
                currentState = State::OFF;            
                break;
        }
    }
}
/*
 Copyright (c) 2022 

All rights reserved to use, copy, modify, and distribute
Authors: Evan BLANC 2079808 and Ahmed ZGHAL 2068299 - TEAM 17
Date:17/10/2022
INF1900
Polytecnhique Montréal ENGINEERING SCHOOl, Canada, Qc

-Explication du programme 1:
Le programme commence par un compteur qui s'incrémente 10 fois par seconde dés que le bouton poussoir est enfoncé  jusqu'a ce 
qu'on relache le bouton poussoir ou bien le compteur atteint 120 ce qui engendre un clignotement vert pendant 0,5 secondes. 
Ensuite on a un temps d'attente de 2 s suivi d'une lumiére rouge qui clignote (compteur / 2) fois au rythme de 2 fois par seconde. 
Dés que la del arrete de clignoter en rouge , elle s'allume en vert pendant 1s . Ensuite la DEL s'éteint et  on revient a l'état initial.

-Identification Materielle
    PIN B OUT (on utilise PB0 et PB1 pour allumer  la DEL respectivement en couleur verte et couleur rouge )
    PIN D IN  (PD2 est reliée au bouton poussoir )

*/
// +────────────────+──────────────────────────────────+──────────────+────────────────────+
// |   STATES:INIT,GREEN_FLASH,WAIT,RED_FLASH,GREEN                                        |
// +────────────────+──────────────────────────────────+──────────────+────────────────────+
// | Present State  | Constraints                      | NextState    | Output             |
// +────────────────+──────────────────────────────────+──────────────+────────────────────+
// | INIT           | Counter < 120 or Button pressed  | GREEN_FLASH  | OFF                |
// | GREEN_FLASH    | Timer of 1/2 second              | WAIT         | BLINKING IN GREEN  |
// | WAIT           | Timer of 2 seconds               | RED_FLASH    | OFF                |
// | RED_FLASH      |(counter / 2)times rythm 2 seconds| GREEN        | BLINKING IN RED    |
// | GREEN          | Timer 1 second                   | INIT         | Green              |
// +────────────────+──────────────────────────────────+──────────────+────────────────────+



#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
const uint8_t LED_RED = 1 << PB1;
const uint8_t LED_GREEN = 1 << PB0;
const uint8_t LED_OFF = ((1<<PB1) & (1<<PB0));
const uint8_t COUNTER_MAX_VALUE = 120;
const uint16_t TIMING_TENTH_SECOND = 781;
const uint16_t TIMING_HALF_SECOND = 2604;
const uint16_t TIMING_ONE_SECOND = 7812;

enum class State
{
    INIT,
    GREEN_FLASH,
    WAIT,
    RED_FLASH,
    GREEN,
};

volatile bool gBtn_released = true;
volatile bool gTime_out = false;
volatile uint8_t gCounter = 0;


/*
 * @brief Set the pin PB0 to HIGH wich turns on the green LED
 * 
 */
const void turnOnGreenLED() {
    PORTB |= LED_GREEN;
}

/*
 * @brief Set the pin PB1 to HIGH wich turns on the red LED
 * 
 */
const void turnOnRedLED() {
    PORTB |= LED_RED;
}


const void turnOffLED() {
    PORTB &= LED_OFF; 
}

/*
 * @brief Flash red LED n times 2 times each seconds
 * 
 */
const void flashRedLED(uint8_t n) {
    for (uint8_t i = 0; i < n/2 ; i++) {
        turnOnRedLED();
        _delay_ms(250);
        turnOffLED();
        _delay_ms(250);
    }
}

void startTimer(uint16_t time) {
    gTime_out = false;

    TCNT1 = 0;
    OCR1A = time;

    TCCR1A = 0;

    TCCR1B = (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    TIMSK1 = 1 << OCIE1A;
}

/* @brief Lance de manière séquentielle COUNTER_MAX_VALUE (120 pour le pb1) minuteries de 10 milisecondes
 * Si le bouton est relaché, la fonction s'arrête
 * Sinon, il incrémente jusqu'à COUNTER_MAX_VALUE puis la fonction s'arrête
 * A la fin, la valeur de compteur a été incrémentée et sauvegardée dans gCounter
 */
void startCounter() {
    for (uint8_t i=0 ; i<COUNTER_MAX_VALUE ; i++) {
        startTimer(TIMING_TENTH_SECOND);
        while (!gTime_out);


        if (gBtn_released) break;
    }
}

ISR (INT0_vect) { // ISR du bouton
    _delay_ms(30);
    gBtn_released = !gBtn_released;
}
 
ISR (TIMER1_COMPA_vect) { // ISR de la minuterie
    gCounter ++;
    gTime_out = true;
}



void initialisation() {
    cli();
        DDRB |= 0xFF;
        DDRD &= 0x00;

        DDRB |= (1 << PB0) | (1 << PB1);
        DDRD &= (0 << PD2);
        EIMSK |= (1 << INT0);
        EICRA |= (1 << ISC00);
    sei();
}

/**
 * @return int 
 */
int main() {
    initialisation();
    uint8_t counter = 0;
    State currentState = State::INIT;

    while (true) {
        switch (currentState) {

            case State::INIT:

                while (gBtn_released);
                startCounter();

                counter = gCounter;
                currentState = State::GREEN_FLASH;
                break;

            case State::GREEN_FLASH:
                turnOnGreenLED();
                _delay_ms(500);
                turnOffLED();
                currentState = State::WAIT;
                break;

            case State::WAIT:
                _delay_ms(2000);
                currentState = State::RED_FLASH;
                break;

            case State::RED_FLASH:
                flashRedLED(counter);
                currentState = State::GREEN;
                break;
            
            case State::GREEN:
                turnOnGreenLED();
                _delay_ms(1000);
                turnOffLED();
                currentState = State::INIT;
                break;
        }
    }
}
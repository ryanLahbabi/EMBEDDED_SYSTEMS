/********************************************************
/* Copyright (c) 2022 
/*
/* All rights reserved to use, copy, modify, and distribute
/* Authors: Evan BLANC 2079808 and Ahmed ZGHAL 2068299 - TEAM 17
/* INF1900
/* Polytecnhique Montréal ENGINEERING SCHOOl, Canada, Qc
*********************************************************/

#include <avr/io.h>
#define F_CPU 8000000U
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

const int DELAY_GREEN_LED = 2000;
const int DELAY_DEBOUNCE = 10;
const int NB_STATES = 4;

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

volatile uint8_t gEtat = 0;
const State[] states = {OFF, INTERM1, INTERM2, GREEN};

void initialisation ( void ) {
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli ();

    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA |= 0xff;
    DDRD &= 0x00;

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0) ;

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC00 | 1 << ISC01) ;

    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR ( INT0_vect ) {
    // laisser un délai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms ( 30 );
    // se souvenir ici si le bouton est pressé ou relâché

    // changements d'état tels que ceux de la
    // semaine précédente
    gEtat = (gEtat++) % NB_STATES; // modulo 4 because there are 4 states so in goes in circle
    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0) ;
}

// /** TODO : REPLACE THIS WITH AN ISR
//  * @brief if the button is pressed for the specified delay time, the function return true, false if not
//  * 
//  * @return true 
//  * @return false 
//  */
// bool isButtonPressed() {    
//     if (PIND & 0x04) 
//     {
//         _delay_ms(DELAY_DEBOUNCE);
//         return PIND & 0x04; 
//     }
//     return false;
//  }

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
 * @brief We used a "swich case" structure to represent the state machine.
 * It allows us to start with initial state, then depending on the currentState, the right action will be executed,
 * and the next state will become the current state, then back to initial state.
 * 
 * @return int 
 */
int main() {
    
    while (true) {
        switch (states[gEtat]) {

            case State::OFF:

                turnLedOff();
                break;

            case State::INTERM1:

                turnLedOff();
                break;

            case State::INTERM2 :

                turnLedOff();
                break;

            case State::GREEN:
                turnLedOnGreen();
                _delay_ms(DELAY_GREEN_LED);
                gEtat = (gEtat++)%4;       
                break;
        }
    }
}
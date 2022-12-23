/*
Copyright (c) 2022 

All rights reserved to use, copy, modify, and distribute
Authors: Evan BLANC 2079808 and Ahmed ZGHAL 2068299 - TEAM 17
Date:17/10/2022
INF1900
Polytecnhique Montréal ENGINEERING SCHOOl, Canada, Qc

-Explication du probléme 2 : 
Le programme permet d'ajuster la sortie des LEDs en fonction de la lumiére détectée par la photoresistance. 
la sortie sera de couleur rouge si l'intensité lumineuse dépasse un seuil Maximal 
la sortie sera de couleur Ambre si l'intensité lumineuse est incluse entre le seuil Minimal et  le  seuil Maximal  
la sortie sera de couleur verte si l'intensité lumineuse est inférieure au un seuil Minimal
 
-Identification Materielle
PIN B OUT (on utilise PB0 et PB1 pour allumer  la DEL respectivement en couleur verte et couleur rouge )
PIN A IN (le fil de données à relié au  port analogique  PA0 )
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <can.h>

can light = can();


const uint8_t LED_RED   = 1 << PB1;
const uint8_t LED_GREEN    = 1 << PB0;


const uint8_t LIGHT_HIGH    = 240;
const uint8_t LIGHT_LOW   = 150;


void initialisation()
{
    DDRA &= 0x00;
    DDRB |= 0xFF;
}
const void turnLedOnGreen() {
    PORTB |= LED_GREEN;
}
const void turnLedOnRed() {
    PORTB |= LED_RED;
}


const void turnLedOnAmber()() {
    turnLedOnGreen();
    _delay_ms(1);
    turnLedOnRed()
    _delay_ms(1);
}

int main()
{
    initialisation();
    while (true)
    {
        uint16_t adcVal = light.lecture(PA0);
        uint8_t lightIntensity = adcVal >> 2;

        if (lightIntensity > LIGHT_HIGH)
            turnLedOnRed()
        else if ((lightIntensity >= LIGHT_LOW) && (lightIntensity <= LIGHT_HIGH))
            turnLedOnAmber()
        else if (lightIntensity < LIGHT_LOW)
            turnLedOnGreen()


    }
}
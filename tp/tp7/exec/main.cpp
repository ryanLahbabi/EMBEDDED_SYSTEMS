
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <interrupt.h>
#include <moteur.h>
#include <del.h>
#include <bouton.h>
#include <debug.h>

volatile bool gDel = false;


ISR(INT0_vect) {
    gDel = !gDel;
}

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;
    DDRB = 0xff;
    DDRC = 0x00;

    Del del;
    Moteur mot(PB5, PB6);
    
    BoutonInterruption::initialiser(INT0, ModeInterruption::FallingEdgeInterrupt);
    
    
    while (true)
    {
        mot.avancer(10);
    }         
}
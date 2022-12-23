#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>

const uint8_t MAX_PWM = 255;

uint8_t sortie()
{
    DDRD |= 0xff;
}

uint8_t entree()
{
    DDRA &= 0x00;
}

void ajustementPwm (uint8_t roue) {
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

    // page 130 de la description technique du ATmega324PA)
    OCR1A = roue; // PWM, Phase Correct sur 8 bits donc le max est a 255(100% ) ;
    OCR1B = roue; // PWM, Phase Correct sur 8 bits donc le max est a 255(100% ) ;

    // division d'horloge par 8 - implique une fréquence de PWM fixe
    TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1); // PWM, Phase Correct sur 8 bits et 
    TCCR1B |= (1 << CS11);  // division de la clock par 8
    TCCR1C = 0;
}

void gererPwm() {
    ajustementPwm(MAX_PWM*0.25);
    _delay_ms(2000);
    ajustementPwm(MAX_PWM*0.5);
    _delay_ms(2000);
    ajustementPwm(MAX_PWM*0.75);
    _delay_ms(2000);
    ajustementPwm(MAX_PWM);
    _delay_ms(2000);
}

int main()
{
    DDRD |= 0xff; 
    
        gererPwm(); 
    
}


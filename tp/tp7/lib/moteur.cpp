#include <moteur.h>

void initialisationMinuterie()
{
    TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS01);
}


Moteur::Moteur(uint8_t pinDirectionDroite, uint8_t pinDirectionGauche)

    : _directionDroite(pinDirectionDroite), _directionGauche(pinDirectionGauche)
{
    DDRB |= (1 << _directionDroite) | (1 << _directionGauche) | (1 << PB3) | (1 << PB4);
}

void Moteur::avancer(uint8_t pourcentagePWM)
{
    initialisationMinuterie();
    OCR0A = pourcentagePWM * MAX_PWM / 100;
    OCR0B = pourcentagePWM * MAX_PWM / 100;
    PORTB &= ~(1 << _directionDroite);
    PORTB &= ~(1 << _directionGauche);

};

void Moteur::reculer(uint8_t pourcentagePWM)
{
    initialisationMinuterie();
    OCR0A = pourcentagePWM * MAX_PWM / 100;
    OCR0B = pourcentagePWM * MAX_PWM / 100;
    PORTB |= ~(1 << _directionDroite);
    PORTB |= ~(1 << _directionGauche);
};

void Moteur::arret()
{
    initialisationMinuterie();
    OCR0A = ARRET;
    OCR0B = ARRET;
};

void Moteur::tourner(uint8_t pourcentageRoueGauche, uint8_t pourcentageRoueDroite)
{
    initialisationMinuterie();
    
    OCR0A = pourcentageRoueDroite * MAX_PWM / 100;
    OCR0B = pourcentageRoueGauche * MAX_PWM / 100;
};

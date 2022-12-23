#include <moteur.h>

void initialisationMinuterie()
{
    TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS01);
}

void Moteur::initialiser()
{
    DDRB |= (1 << _directionDroite) | (1 << _directionGauche) | (1 << PB3) | (1 << PB4);
}

void Moteur::avancer(Pwm pourcentagePWM)
{
    initialisationMinuterie();

    OCR0A = static_cast<uint8_t>(pourcentagePWM) * static_cast<uint8_t>(Pwm::MAX) / 100;
    OCR0B = static_cast<uint8_t>(pourcentagePWM) * (static_cast<uint8_t>(Pwm::MAX) + 20) / 100;

    PORTB &= ~(1 << _directionDroite);
    PORTB &= ~(1 << _directionGauche);
};

void Moteur::reculer(Pwm pourcentagePWM)
{
    initialisationMinuterie();

    OCR0A = static_cast<uint8_t>(pourcentagePWM) * static_cast<uint8_t>(Pwm::MAX) / 100;
    OCR0B = static_cast<uint8_t>(pourcentagePWM) * static_cast<uint8_t>(Pwm::MAX) / 100;
    PORTB |= ~(1 << _directionDroite);
    PORTB |= ~(1 << _directionGauche);
};

void Moteur::arret()
{
    initialisationMinuterie();

    OCR0A = static_cast<uint8_t>(Pwm::ARRET);
    OCR0B = static_cast<uint8_t>(Pwm::ARRET);
};

void Moteur::tourner(Pwm pourcentageRoueGauche, Pwm pourcentageRoueDroite)
{
    initialisationMinuterie();
    
    PORTB &= ~(1 << _directionDroite);
    PORTB &= ~(1 << _directionGauche);
    OCR0A = static_cast<uint8_t>(pourcentageRoueDroite) * static_cast<uint8_t>(Pwm::MAX) / 100;
    OCR0B = static_cast<uint8_t>(pourcentageRoueGauche) * static_cast<uint8_t>(Pwm::MAX) / 100;
};

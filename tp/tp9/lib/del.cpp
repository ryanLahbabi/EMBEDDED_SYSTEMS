#include <del.h>

void Del::initialiser()
{
    DDRA |= 0xff;
}

void Del::allumerCouleurLumiere(Couleur couleur)
{
        PORTA = couleur;       
}

void Del::clignoter(uint8_t nbFois, Couleur couleur)
{
    for (uint8_t i = 0; i < nbFois; i++)
    {
        allumerCouleurLumiere(couleur);
        _delay_ms(DELAIS_CLIGNOTER);
        allumerCouleurLumiere(Couleur::ETEINTE);
        _delay_ms(DELAIS_CLIGNOTER);
    }
}

void Del::ambrer()
{
    allumerCouleurLumiere(Couleur::VERTE);
    _delay_ms(DELAIS_AMBRER_VERT);
    allumerCouleurLumiere(Couleur::ROUGE);
    _delay_ms(DELAIS_AMBRER_ROUGE);
}

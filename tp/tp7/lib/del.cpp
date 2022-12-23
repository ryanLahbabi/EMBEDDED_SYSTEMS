#include <del.h>

Del::Del()
{
    DDRA |= 0xff;
}


void Del::setCouleurLumiere(Couleur couleur)
{
        PORTA = couleur;       
}

void Del::clignoter(uint8_t nbFois, Couleur couleur)
{
    for (uint8_t i = 0; i < nbFois; i++)
    {
        setCouleurLumiere(couleur);
        _delay_ms(DELAIS_CLIGNOTER);
        setCouleurLumiere(Couleur::ETEINTE);
        _delay_ms(DELAIS_CLIGNOTER);
    }
}

void Del::ambrer()
{
    setCouleurLumiere(Couleur::VERTE);
    _delay_ms(DELAIS_AMBRER_VERT);
    setCouleurLumiere(Couleur::ROUGE);
    _delay_ms(DELAIS_AMBRER_ROUGE);
}

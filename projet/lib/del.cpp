#include <del.h>
#include <usart.h>

void Del::initialiser()
{
    DDRD |= 0xff;
    DDRD &= ~(1 << PD2);
}

void Del::allumerCouleurLumiere(Couleur couleur)
{
    PORTD = couleur;       
}

void Del::clignoter(uint8_t duree, uint8_t frequence, Couleur couleur)
{
    uint8_t delay = 1000/(2*frequence);    
        
    for (uint8_t i = 0; i < duree*frequence; i++)
    {
        allumerCouleurLumiere(couleur);
        for (uint8_t t = 0; t < (delay)/100; t++) 
            _delay_ms(100);
        allumerCouleurLumiere(Couleur::ETEINTE);
        for (uint8_t t = 0; t < (delay)/100; t++) 
            _delay_ms(100);
    }
}

void Del::ambrer()
{
    allumerCouleurLumiere(Couleur::VERTE);
    _delay_ms(DELAIS_AMBRER_VERT);
    allumerCouleurLumiere(Couleur::ROUGE);
    _delay_ms(DELAIS_AMBRER_ROUGE);
}

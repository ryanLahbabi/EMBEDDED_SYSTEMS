#include <bouton.h>

bool Bouton::appuiBouton()
{
    if (PIND & (1<<PD2))
    {
        _delay_ms(ANTI_REBOND);
        return PIND & (1<<PD2); 
    }
    return false;
}

void Bouton::initialiser()
{
    DDRD &= ALL_IN;
}

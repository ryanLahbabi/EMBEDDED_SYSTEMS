#include <bouton.h>

bool Bouton::appuiBouton()
{
    if (PINA & (1<<PA0))
    {
        _delay_ms(ANTI_REBOND);
        return PINA & (1<<PA0); 
    }
    return false;
}

void Bouton::initialiser()
{
    DDRA &= ALL_IN;
}

#include <bouton.h>


/**
 * @brief Verify if the button is pressed by scrutation
 * 
 * @return true if button is pressed
 * @return false otherwise
 */
bool Bouton::appuiBouton()
{
    if (PIND & (1<<PD2))
    {
        _delay_ms(ANTI_REBOND);
        return PIND & (1<<PD2); 
    }
    return false;
}

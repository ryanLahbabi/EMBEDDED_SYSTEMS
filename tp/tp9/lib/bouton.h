#ifndef F_CPU
    #define F_CPU 8000000UL
#endif
#include <util/delay.h>
#include <avr/io.h>

const uint8_t ALL_IN = 0x00;
const uint8_t ANTI_REBOND = 10;

class Bouton
{
public:

    /**
     * @brief Set PORTD to 1
     * 
     */
    static void initialiser();
    
    /**
     * @brief Verify if the button is pressed by scrutation
     * 
     * @return true if button is pressed
     * @return false otherwise
     */
    static bool appuiBouton();
};

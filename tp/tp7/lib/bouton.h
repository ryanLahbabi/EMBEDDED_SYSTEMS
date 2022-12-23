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
    Bouton()
    {
        DDRD &= ALL_IN;
    };

    bool appuiBouton();
};

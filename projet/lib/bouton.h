#ifndef F_CPU
    #define F_CPU 8000000UL
#endif
#include <util/delay.h>
#include <avr/io.h>

const uint8_t ALL_IN = 0x00;
const uint8_t ANTI_REBOND = 30;

class Bouton
{
public:
    /**
     * @brief Fixer PORTA à 1
     * 
     */
    static void initialiser();
    
    /**
     * @brief Vérifier si le bouton est appuyé par scrutation
     * 
     * @return true si  le bouton est appuyé
     * @return false sinon
     */
    static bool appuiBouton();
};

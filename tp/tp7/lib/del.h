#ifndef F_CPU
    #define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

const uint8_t OFF = 0x00;
enum Couleur {

    ETEINTE = OFF,
    ROUGE = (1 << PA0),
    VERTE = (1 << PA1),
};

const uint8_t DELAIS_CLIGNOTER = 250;  
const uint8_t DELAIS_AMBRER_VERT = 10;
const uint8_t DELAIS_AMBRER_ROUGE = 5;


class Del
{
public:
    Del();

     /**
     * @param Couleur couleur (couleur de la DEL qui provient de l enum class Couleur)
     * 
     * Fonction qui fait allume la DEL de la couleur demandee
     **/
    void setCouleurLumiere(Couleur couleur);

    /**
     * @param uint8_t nbFois (nombre de clignotements)
     * @param Couleur couleur (couleur de la DEL qui provient de l enum class Couleur)
     * 
     * Fonction qui fait clignoter la DEL de la couleur demandee
     **/
    void clignoter(uint8_t nbFois, Couleur couleur);

    /**
     *  Fonction a mettre dans une boucle, allume la led en couleur ambre 
     **/
    void ambrer();


};
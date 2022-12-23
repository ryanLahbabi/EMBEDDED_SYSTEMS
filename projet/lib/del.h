#ifndef F_CPU
    #define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

const uint8_t OFF = 0x00;
enum Couleur {

    ETEINTE = OFF,
    ROUGE = (1 << PD6),
    VERTE = (1 << PD7),
};

const uint8_t DELAIS_AMBRER_VERT = 10;
const uint8_t DELAIS_AMBRER_ROUGE = 5;


class Del
{
public:
     /**
      * @brief Fonction qui initialise le port A pour la led
      * 
     **/
    static void initialiser();

    /**
     * @brief Fonction qui fait allume la DEL de la couleur demandee
     * 
     * @param Couleur couleur (couleur de la DEL qui provient de l enum class Couleur)
     **/
    static void allumerCouleurLumiere(Couleur couleur);

    /**
     * @brief Fonction qui fait clignoter la DEL de la couleur demandee
     * 
     * @param uint8_t duree (en seconde)
     * @param uint8_t frequence (nombre de clignotements par seconde)
     * @param Couleur couleur (couleur de la DEL qui provient de l enum class Couleur)
     **/
    static void clignoter(uint8_t duree, uint8_t frequence, Couleur couleur);

    /**
     *  @brief Fonction a mettre dans une boucle, allume la led en couleur ambre 
     **/
    static void ambrer();
};
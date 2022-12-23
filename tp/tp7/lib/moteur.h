#pragma once

#ifndef F_CPU
    #define F_CPU 8000000UL
#endif
#include <avr/io.h>


const uint8_t ARRET = 0;
const uint8_t MAX_PWM = 255;

/**
 * @brief Class Moteur configurée pour PORTB
 * 
 */
class Moteur
{
public:
    Moteur(uint8_t pinDirectionDroite, uint8_t pinDirectionGauche); // constructeur 

    /**
     * @brief Faire avancer le robot
     * 
     * @param pourcentagePWM : pourcentage de vitesse max
     */
    void avancer(uint8_t pourcentagePWM);
  
    /**
     * @brief Faire reculer le robot
     * 
     * @param pourcentagePWM : pourcentage de vitesse max
     */
    void reculer(uint8_t pourcentagePWM);

    /**
     * @brief Arreter le robot
     * 
     */
    void arret();

    /**
     * @brief Faire tourner le robot en ajustant la vitesse de chaque moteur indépendament
     * 
     * @param pourcentageRoueGauche 
     * @param pourcentageRoueDroite 
     */
    void tourner(uint8_t pourcentageRoueGauche, uint8_t pourcentageRoueDroite);

private:
    uint8_t _directionDroite;
    uint8_t _directionGauche;

};

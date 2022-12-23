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
    static void initialiser(); 

    /**
     * @brief Faire avancer le robot
     * 
     * @param pourcentagePWM : pourcentage de vitesse max
     */
    static void avancer(uint8_t pourcentagePWM);
  
    /**
     * @brief Faire reculer le robot
     * 
     * @param pourcentagePWM : pourcentage de vitesse max
     */
    static void reculer(uint8_t pourcentagePWM);

    /**
     * @brief Arreter le robot
     * 
     */
    static void arret();

    /**
     * @brief Faire tourner le robot en ajustant la vitesse de chaque moteur indépendament
     * 
     * @param pourcentageRoueGauche 
     * @param pourcentageRoueDroite 
     */
    static void tourner(uint8_t pourcentageRoueGauche, uint8_t pourcentageRoueDroite);

    static const uint8_t _directionDroite = PB5;
    static const uint8_t _directionGauche = PB6;

};

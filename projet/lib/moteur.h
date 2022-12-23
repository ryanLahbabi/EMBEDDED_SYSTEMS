#pragma once

#ifndef F_CPU
    #define F_CPU 8000000UL
#endif
#include <avr/io.h>

enum class Pwm {

    ARRET = 0,
    MAX = 255,
    AVANCER = 40,
    AVANCER_AB = 60,
    AVANCER_BS = 60,
    AVANCER_TOURNER = 45,
    AVANCER_TOURNER_AB = 50,
    TOURNER = 10,
    DEFAULT = 30,
    AVANCER_BASE = 60, 

    AVANCER_TOURNER_CHOIX = 80,

    AVANCER_ZIGZAG = 55,
    AVANCER_TOURNER_ZIGZAG_DROITE = 55,
    AVANCER_TOURNER_ZIGZAG_GAUCHE = 55,
    TOURNER_ZIGZAG = 0,

    AVANCER_PARK = 40,
    RECULER_PARK = 60,
    TOURNER_PARK = 100
};

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
     *
     * @param delai : temps d'attente apres l'action
     */
    static void avancer(Pwm pourcentagePWM);

    /**
     * @brief Faire reculer le robot
     * 
     * @param pourcentagePWM : pourcentage de vitesse max
     * 
     * @param delai : temps d'attente apres l'action
     */
    static void reculer(Pwm pourcentagePWM);

    /**
     * @brief Arreter le robot
     * 
     * @param delai : temps d'attente apres l'action
     */
    static void arret();

    /**
     * @brief Faire tourner le robot en ajustant la vitesse de chaque moteur indépendament
     * 
     * @param pourcentageRoueGauche 
     * @param pourcentageRoueDroite 
     * @param delai : temps d'attente apres l'action
     */
    static void tourner(Pwm pourcentageRoueGauche, Pwm pourcentageRoueDroite);

    static const uint8_t _directionDroite = PB5;
    static const uint8_t _directionGauche = PB6;

};

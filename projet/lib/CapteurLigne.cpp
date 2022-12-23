#include "CapteurLigne.h"

/**
 * @brief Module3: Suivi de ligne
 * 
 * Utilisation du _capteur de ligne "Maker Line de Cytron".
 * Il est composé de 5 _capteurs nommés u1, u2, u3, u4 et u5 qui sont
 * branchés sur notre robot comme indiqué ci-dessous :
 *
 *      -Sur la carte:
 *          u1: broche 4 ; u2: broche 3 ; u3: broche 6 ; u4: broche 5 ; u5: broche 8
 * 
 *     -Dans le code:
 *          u1: pin 3 ; u2: pin 2 ; u3: pin 5 ; u4: pin 4 ; u5: pin 7
 * 
 * Le port que nous utilisons est le PORTC dédié uniquement à ce _capteur dans notre montage.
 * 
 * Nous avons identifiés plusieurs états du _capteur en fonction de la situation et y avons
 * associé les sorties correspondantes:
 * 
 *      -Etat_1: Tous les _capteurs captent la ligne:
 *          Nous sommes positionnés sur une zone d'arrivée ou base.
 * 
 *      -Etat_2: Une combinaison des _capteurs de gauche captent la ligne:
 *          Nous devont corriger la trajectoire en tournant à gauche.
 * 
 *      -Etat_3: Une combinaison des _capteurs de droite captent la ligne:
 *          Nous devont corriger la trajectoire en tournant à droite.
 * 
 *      -Etat_4: Le _capteur central et une combinaison des _capteurs de droite et gauche captent la ligne:
 *          Nous devont continuer à avancer tout droit.
 * 
 *      -Etat_5: Le _capteur central est éteind et tous les autres captent la ligne:
 *          Nous devons choisir un chemin (Gauche ou Droite).
 * 
 *      -Etat_6: Aucun _capteur ne capte la ligne:
 *          Nous executons le mouvement précédent.
 *      
 *      Par défault si nous sommes dans un état inconnu:
 *          Le robot avance lentement.
 * 
 * 
 * Le code ci-dessous a été réfléchi et écrit par les membres de l'équipe 1617 du cours INF1900:
 * @authors Evan BLANC, Ahmed ZGHAL, Ali MOUCHAHID, Ryan LAHBABI.
 */
Mouvement CapteurLigne::choisirMouvement() {

    switch (PINC & 0b10111100) {
            case (U1 + U2 + U3 + U4 + U5):
                return Mouvement::ARRET;
            break;

            case (U5 + U4 + U2 + U1):
            case (U5 + U2 + U1):
            case (U5 + U4 + U1):
            case (U5 + U1):
            case (U2 + U3 + U4):
                return Mouvement::CHOIX;
            break;

            case (U1 + U2 + U3):
            case (U1 + U2):
            case (U2 + U3):
            case U1:
            case U2:
                return Mouvement::TOURNER_GAUCHE;
            break;

            case (U3 + U4 + U5):
            case (U4 + U5):
            case (U4 + U3):
            case U5:
            case U4:
                return Mouvement::TOURNER_DROITE;
            break;

            case U3:
                return Mouvement::AVANCER;
            break;

            case 0:
                return Mouvement::ANCIEN;
            break;  

            default:
                return Mouvement::DEFAUT;
            break;    
        }
}
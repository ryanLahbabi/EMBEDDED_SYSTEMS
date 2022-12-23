/*
Travail : TRAVAIL_PRATIQUE 6, Problème 2
Section # : 02
Équipe # : EQUIPE_NO 16
Auteurs : Ryan Lahbabi, Ali Mouchahid   

Description du programme: Le programme ci-dessous répond au problème 2:
Ce porgramme permet de compiler sur un processeur atmega 324 la détection de la lumière capter par une photorésistance. En fonction de la lumière recu par la photorésistance, 
la DEL change de couleur. Lorsque la lumière reçu est intense, comme pour une lampe de poche la DEL devient rouge. Lorsque la photorésistance reçoit une lumière ambiante, 
la DEL devient ambrer, elle clignote à très grande vitesse entre rouge et vert. Notre fontion ambrer permet d'établir ce clignotement qui ne se voit pas a vu d'oeil. 
Enfin lorsque la photoresistance ne capte aucune lumière ou presque, la DEL Devient verte.

Identifications matérielles (Broches I/O):
Nous avons fais en sorte d'avoir en référence analogique +5.0 volts sur notre robot afin de régler le voltage de sortie du diviseur.
Utilisation d'une résistance 10K (brun-noir-orange) (Digi-Key: S10KQTR-ND) placer en série avec une photorésistance (Digi-Key: PDV-P8101-ND) 
sur le breadbord connectés avec un fil de données reliés à deux PIN du DDRA et un fil d'alimentation reliés au VCC de l'Atmega 324
INT 0/1: DDRA --> Cet input prend comme valeur 0 ou 1 afin de savoir si le courant passe ou non.
Analog Digital Converter: PB0; PB1; DDRB --> Ces Output ressort le courant conduit par la photorésistance. 
PB0 ressort le courant afin d'allumer la DEL bicoolore en vert et PB1 allume la DEL bicolore en rouge
Les valeur de adcVal ot été obtenue après plusieurs tests avec différents éclairage jusqu'à avoir les résultats attendus.

IMPORTANT: Les valeurs de LIMITE_LUMIERE_FAIBLE et LIMITE_LUMIERE_AMBIANTE peuvent changer en fonction du robot, nous avons pour notrer part des va
leurs pas mal elever mais nous sommes consicent qu'elles risquent de changer lorsque vous allez tester le robot. 
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "can.h"

can lumiere = can();

const uint8_t BITSHIFT = 2;
const uint8_t PIN = 1;
const uint8_t LIMITE_LUMIERE_FAIBLE = 200;
const uint8_t LIMITE_LUMIERE_AMBIANTE = 240;
const uint8_t DELAIS_AMBRER_VERT = 10;
const uint8_t DELAIS_AMBRER_ROUGE = 5;

void initialisation()
{
    DDRA &= ~(1 << DDA0);
    DDRB |= (1 << DDB0) | (1 << DDB1);
}
void allumerVert()
{
    PORTB |= (1 << PB0);
}
void allumerRouge()
{
    PORTB |= (1 << PB1);
}

void ambrer()
{
    allumerVert();
    _delay_ms(DELAIS_AMBRER_VERT);
    allumerRouge();
    _delay_ms(DELAIS_AMBRER_ROUGE);
}

int main()
{
    initialisation();
    uint8_t valeurLumiere;

    while (true)
    {
        valeurLumiere = (lumiere.lecture(PIN) >> BITSHIFT); 
        if (valeurLumiere < LIMITE_LUMIERE_FAIBLE)
            allumerVert();

        else if (valeurLumiere >= LIMITE_LUMIERE_AMBIANTE) 
            allumerRouge();

        else if( (valeurLumiere >= LIMITE_LUMIERE_FAIBLE) && (valeurLumiere < LIMITE_LUMIERE_AMBIANTE))
            ambrer();
    }
}



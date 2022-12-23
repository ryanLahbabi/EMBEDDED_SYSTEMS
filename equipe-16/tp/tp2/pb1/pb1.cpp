// Travail : TRAVAIL_PRATIQUE 2
//Section # : 01
//Équipe # : EQUIPE_NO 16
// Correcteur : Charles Jiang
/*
+-------------------------------------------------------------+
|                                                             |
| Problème 1 
+-------------------------------------------------------------+
|                                                             |
| ETATS : ETEINT, INTERM1, INTERM2, VERT 
+---------------------+-------------------+-------------------+
| Entrée              | États prochain    | États présents    |
+---------------------+-------------------+-------------------+
|                     |                   |                   |
| Bouton interrupt    | INTERM1           | ETEINT            |
+---------------------+-------------------+-------------------+
|                     |                   |                   |
| Bouton interrupt    | INTERM2           | INTERM1 |
+---------------------+-------------------+-------------------+
|                     |                   |                   |
| Bouton interrupt    | VERT              | INTERM2           |
+---------------------+-------------------+-------------------+
|                     |                   |                   |
| Bouton interrupt    | ETEINT            | VERT              |
+---------------------+-------------------+-------------------+

// Description du programme: Le programme ci-dessous répond au problème 1.
//Ce porgramme permet compiler sur un microprocesseur atmega 324 une machine à état(voir ci-dessous)
//imposer par l'énoncé qui passe la couleur d'une LED a l'état  vert pendant 2 secondes apres 3 appui sur le bouton pour enfin s'eteindre et revenir a l'etat initial.
//Le programme prend en compte l'état courant afin de savoir quel sera l'état prochain.
//On remarquera que à l'état initial la DEl est ETEINT. Afin de traiter le problème de debounce,
//nous avons utilisé une fonction appuiBouton et l'on a inclus un délais anti_rebond de 10 ms.
//Aussi nous avons déclaré nos 4 États ETEINTS, INTERM1, INTERM2 et VERT,afin de pouvoir les référer à notre switch case(etatcourant)
//Identifications matérielles (Broches I/O):
//
//INT 0/1: PIND2; PIND3; DDRD --> Ces input prennent comme valeur 0 ou 1 afin de savoir si le courant passe ou non.
//Analog Digital Converter: PA0; PA1; DDRA --> Cet Output ressort le courant conduit par le boutons interrupt
// et qui a été traité par le microprocesseur atmega afin d'allumer la LED en rouge(PA0) ou VERT(PA1), cela change en fonction de la polarite du cable.
*/





#include <avr/io.h>
#define F_CPU 8000000U
#include <util/delay.h>
#include <stdint.h>

const int DELAIS_VERT = 2000;
const int DELAIS_ANTIREBOND = 10;

const  void eteindre(){
    PORTA &= (1 << PA1) & (1<<PA0);
}

const void allumerVert(){
     PORTA |= (1 << PA1);
}

bool appuiBouton()
{    
    if (PIND & 0x04) 
    {
        _delay_ms(DELAIS_ANTIREBOND);
        return PIND & 0x04; 
    }
    return false;
 }

enum class Etat
{
    ETEINT,
    INTERM1,
    INTERM2,
    VERT
};

int main()
{

    DDRA |= 0xff;
    DDRD |= 0x00;

    Etat etatCourant = Etat::ETEINT;

    while (true)
    {
        switch (etatCourant)
        {

            case Etat::ETEINT :

                eteindre();
                while (appuiBouton()) 
                {
                    etatCourant = Etat::INTERM1;
                }
                
                break;

            case Etat::INTERM1 :

                eteindre();
                while (appuiBouton())
                {
                    etatCourant = Etat::INTERM2;
                }
                break;

            case Etat::INTERM2 :

                eteindre();
                while (appuiBouton())
                {
                    etatCourant = Etat::VERT;

                }
                break;

            case Etat::VERT :
                allumerVert();
                _delay_ms(DELAIS_VERT);
                etatCourant = Etat::ETEINT;            
                break;
        }
    }
}

// Travail : TRAVAIL_PRATIQUE 2
//Section # : 01
//Équipe # : EQUIPE_NO 16
// Correcteur : Charles Jiang
/*
+----------------------------------------------------------------------+
|                                                                      |
| Problème 2                                                           |
+----------------------------------------------------------------------+
|                                                                      |
| ETATS : ROUGE, AMBRE, VERT, ETEINT                                   |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Entrée                       | États prochain    | États présents    |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Bouton interrupt(appuyer)    | AMBRE             | ROUGE             |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Bouton interrupt(lâcher)     | VERT              | AMBRE             |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Bouton interrupt(appuyer)    | ROUGE             | VERT              |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Bouton interrupt(lâcher)     | ETEINT            | ROUGE             |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Bouton interrupt(appuyer)    | VERT              | ETEINT            |
+------------------------------+-------------------+-------------------+
|                              |                   |                   |
| Bouton interrupt(lâcher)     | ROUGE             | VERT              |
+------------------------------+-------------------+-------------------+

// Description du programme: Le programme ci-dessous répond au problème 2.
//Ce porgramme permet compiler sur un microprocesseur atmega 324 une machine à état(voir ci-dessous)
//imposer par l'énoncé qui passe la couleur d'une LED entre rouge et noir en fonction du bouton où l'on appuie entre les boutons D2 et D3.
//Le programme prend en compte l'état courant afin de savoir quel sera l'état prochain.
//On remarquera que à l'état initial la DEl est ROuge. Afin de traiter le problème de debounce,
//nous avons utilisé une fonction appuiBouton et l'on a inclus un délais anti_rebond de 10 ms.
//Aussi nous avons déclaré nos 4 États ETEINTS ROUGE, VERT, AMBRER afin de pouvoir les référer à notre switch case(etatcourant)
//Enfin les constantes pour les délais de l'état ambré sont différentes pour le vert et le rouge. Nous avons testé ces valeurs
 jusqu'à avoir une couleur ambrer, nous avons dû mettre un délai plus grand pour le vert car le vert est une couleur plus faible que le rouge.  

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
const int DELAIS_AMBRE_ROUGE = 1;
const int DELAIS_AMBRE_VERT = 15;

bool rougeAppui = false;
bool vertAppui = false;

const void eteindre(){
     
    PORTA &= ~((1 << PA1) | (1<<PA0));
}

const void allumerVert(){
    PORTA = (1 << PA1);
}
const void allumerRouge(){
    PORTA = (1 << PA0);
}



void allumerAmbre(){
    allumerVert();
    _delay_ms(DELAIS_AMBRE_VERT);
    allumerRouge();
    _delay_ms(DELAIS_AMBRE_ROUGE);
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
    ROUGE,
    VERT,
    AMBRE
};

int main()
{
    DDRA |= 0xff;
    DDRD |= 0x00;


    Etat etatCourant = Etat::ROUGE;
  
    while (true)
    {
        switch (etatCourant)
        {
            case Etat::ROUGE :
                
                if (rougeAppui == false)
                {
                    allumerRouge(); 
                    if (appuiBouton()) 
                        etatCourant = Etat::AMBRE;          
                }
                
                else 
                {    
                    if (appuiBouton()) 
                    {
                        while (appuiBouton())
                            allumerRouge();                   
                                      
                        etatCourant = Etat::ETEINT;
                        rougeAppui = false; 
                    }
                }
                break;


            case Etat::AMBRE :
               
                while (appuiBouton()){
                    allumerAmbre();
                }
            
                    etatCourant = Etat::VERT;
                
                break;


            case Etat::ETEINT :

                eteindre();
                if (appuiBouton()) 
                    etatCourant = Etat::VERT;

                vertAppui = true;
                break;


            case Etat::VERT :

                allumerVert();
                if ((vertAppui == false) && (appuiBouton()))
                {
                    rougeAppui = true;
                    etatCourant = Etat::ROUGE; 
                }
                
                else if ((vertAppui == true) && (!appuiBouton()))
                {           
                    rougeAppui = false;
                    vertAppui = false;
                    etatCourant = Etat::ROUGE;
                }
                break;
        }
    }
}

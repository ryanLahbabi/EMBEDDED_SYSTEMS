#define F_CPU 8000000
#include <util/delay.h>
#include <memoire_24.h>
#include <interrupt.h>
#include <moteur.h>
#include <del.h>
#include <bouton.h>
#include <debug.h>
#include <sonorite.h>
#include <stdlib.h>
#include <chargementMemoireExterne.h>

/*
 * @brief Tableau descriptifs des instructions binaires.
 * @authors Ryan Lahbabi , Ali Mouchahid, Evan Blanc, Ahmed Zghal.
 * 
 *   | Instruction binaire | mnémonique | Description                 |	
 *   |--------------------|------------|------------------------------|
 *   | 0000 0001          | DBT        | début                        |
 *   | 0000 0010          | ATT        | attendre                     |
 *   | 100 0100           | DAL        | allumer la DEL               |
 *   | 100 0101           | DET        | éteindre la DEL              |
 *   | 100 1000           | SGO        | jouer une sonorité           |
 *   | 0000 1001          | SAR        | arrêter de jouer la sonorité |
 *   | 110 0000           | MAR        | arrêter les moteurs          |
 *   | 110 0001           | MAR        | arrêter les moteurs          |
 *   | 110 0010           | MAV        | avancer                      |
 *   | 110 0011           | MRE        | reculer                      |
 *   | 110 0100           | TRD        | tourner à droite             |
 *   | 110 0101           | TRG        | tourner à gauche             |
 *   | 1100 0000          | DBC        | début de boucle              |
 *   | 1100 0001          | FBC        | fin de boucle                |
 *   | 1111 1111          | FIN        | fin                          |
 */

const uint16_t DBT = 0x01;
const uint16_t ATT = 0x02;
const uint16_t DAL = 0x44;
const uint16_t DET = 0x45;
const uint16_t SGO = 0x48;
const uint16_t SAR = 0x09;
const uint16_t MAR = 0x60;
const uint16_t MAR_AUTRE = 0x61;
const uint16_t MAV = 0x62;
const uint16_t MRE = 0x63;
const uint16_t TRD = 0x64;
const uint16_t TRG = 0x65;
const uint16_t DBC = 0xC0;
const uint16_t FBC = 0xC1;
const uint16_t FIN = 0xFF;

class Modele {
    private:

        Memoire24CXXX m;
        ChargementMemoireExterne charge; 

        uint16_t addresseInitiale = 0x00;
        uint8_t instruction = 0x00;
        uint8_t operande = 0x00;
        uint8_t iterateur = 0x00;
        uint8_t adresseParcours = 0x00;
        bool fin  = false;
        uint8_t adresseDBC = 0x00;
        uint8_t adresseFBC = 0x00;

        void choix() {
                switch (instruction)
                {
                    case DAL:   
                        Usart::transmettreChaineCaractere("DAL");
                        if(operande==1)
                            Del::allumerCouleurLumiere(VERTE);
                        else if (operande==2)
                            Del::allumerCouleurLumiere(ROUGE);
                    break;

                    case DET:   
                        Del::allumerCouleurLumiere(ETEINTE);
                    break;    
            
                    case SGO: 
                        Usart::transmettreChaineCaractere("SGO");
                        if ( (operande < 45) || (operande > 81) )
                            break;      
                        Sonorite::jouerNote(operande);
                    break;

                    case SAR:
                        Sonorite::arreter();   
                    break;

                    case MAR_AUTRE:
                        Moteur::arret();
                    break;
                    

                    case MAR:
                        Moteur::arret();
                    break;

                    case MAV: 
                        Usart::transmettreChaineCaractere("MAV");
                        Moteur::avancer((operande*100)/255);
                    break;    

                    case MRE:   
                        Moteur::reculer((operande*100)/255);
                    break;   
                    
                    case TRD:    
                        Moteur::tourner(50,0);
                    break; 

                    case TRG:    
                        Moteur::tourner(0,50);
                    break; 

                    case ATT: 
                        for (int i = 0; i < operande; i++)
                            _delay_ms(25);
                    break;
                
                    case DBC:    
                        adresseDBC = adresseParcours;
                        iterateur = operande;
                    break;

                    case FBC:
                        if (iterateur != 0x00)
                            adresseParcours = adresseDBC;
                        iterateur--;
                    break;

                    case FIN:    
                        Moteur::arret();
                        Del::allumerCouleurLumiere(ETEINTE);
                        fin = true;
                    break;
                }
            adresseParcours += 2;
        }

    public:
        Modele() {
            DDRA |= 0xff;
            DDRB |= 0xff;
            DDRC |= 0xff;
            DDRD |= 0xff;

            Moteur::initialiser();
            Del::initialiser();
            Usart::initialiser();
        }

        void exec() {
            do {
                m.lecture(adresseParcours++, &instruction);
                _delay_ms(5);
                m.lecture(adresseParcours++, &operande);
                _delay_ms(5);
            } while (instruction != DBT);

            Del::clignoter(5, VERTE);   

            while (!fin)
            {
                m.lecture(adresseParcours, &instruction);
                _delay_ms(10);
                m.lecture(adresseParcours + 1, &operande);
                _delay_ms(10);
            }
        }
};
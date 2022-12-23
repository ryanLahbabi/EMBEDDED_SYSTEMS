#include "moteur.h"
#include "Materiel.h"
#include "sonorite.h"
#include "math.h"
#include <util/delay.h>

enum class Etape {
    A_VERS_B = 0,
    B_VERS_S = 1,
    S_VERS_FIN = 2,
    ZIGZAG = 3
};

const uint16_t DUREE_SUIVI_LIGNE = 6000;

const uint8_t NB_ZIGZAG = 6;

const uint8_t DISTANCE_PROCHE_MIN = 20;
const uint8_t DISTANCE_PROCHE_MAX = 30;
const uint8_t DISTANCE_LOIN_MIN = 60;
const uint8_t DISTANCE_LOIN_MAX = 80;

const uint8_t POTEAU_PROCHE = 0x0F;
const uint8_t POTEAU_LOIN = 0xF0;




class Robot {
    public:
        Robot() {
            DDRA &= 0x00;
            DDRB |= 0xff;
            DDRC &= 0x00;
            DDRD |= 0b11110011;
        };

        void start();

        void executerMouvement();
        void executerMouvement(uint16_t duree_ms);
        void executerAncienMouvement();
        void choisirChemin();
        bool estSurUneBase();

        void choisirEtape();
        void executerEtape();
        void executerEtape_A_B();
        void executerEtape_B_S();
        void executerEtape_S_FIN();

        void ecrireMemoire();
        void lireMemoire();
        void lirePoteau();
        
        uint8_t getDistance();
        bool parcoursFini();
        bool etapeFinie();

        void tournerGauche();
        void tournerDroite();
        void avancer();
        void avancer(Pwm pwm);
        void arret();
        void zigzag(uint8_t nbVirageDroite);
        void park();

    private:
        // Vaut 0 si avancer, 1 si tourner droite, 2 si tourner gauche.
        uint8_t _ancienMouvement = 0;
        uint8_t _poteaux[3] = {0x00, 0x00, 0x00};
        uint8_t _indexPoteau = 0;

        bool _finEtape = false;
        bool _finParcours = false;

        Materiel _materiel;

        Etape _etape = Etape::A_VERS_B;
        uint8_t _nbChoix = 0;
        bool _autorise = false;
};
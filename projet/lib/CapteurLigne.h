#include <avr/io.h>

enum Mouvement {
    AVANCER,
    TOURNER_GAUCHE,
    TOURNER_DROITE,
    ARRET,
    CHOIX,
    ANCIEN,
    DEFAUT
};

const uint8_t U1 = 8;
const uint8_t U2 = 4;
const uint8_t U3 = 32;
const uint8_t U4 = 16;
const uint8_t U5 = 128;

class CapteurLigne {
    public:
        Mouvement choisirMouvement();
};
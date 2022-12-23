#include "memoire_24.h"
#include "can.h"
#include "CapteurLigne.h"
#include "del.h"
#include "usart.h"
#include "bouton.h"
#include "interrupt.h"

enum class Distance {
    LOIN_MIN = 65,
    LOIN_MAX = 75,
    PROCHE_MIN = 25,
    PROCHE_MAX = 35
};

class Materiel {
    public:
        CapteurLigne getCapteurLigne() { return _capteurLigne;}
        Memoire24CXXX getMemoire() { return _memoire;}
        can getCapteurDistance() { return _capteurDistance;}

    private:
        CapteurLigne _capteurLigne;
        Memoire24CXXX _memoire;
        can _capteurDistance;
};
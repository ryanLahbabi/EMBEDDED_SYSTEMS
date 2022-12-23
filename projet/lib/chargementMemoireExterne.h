#define F_CPU 8000000

#include "memoire_24.h"

#include "usart.h"

#include <util/delay.h>

class ChargementMemoireExterne {
    public:
        ChargementMemoireExterne();

        void ecritureDonnees();

    private:
        Memoire24CXXX _memoire;

        uint16_t _nbTotalOctets;
};

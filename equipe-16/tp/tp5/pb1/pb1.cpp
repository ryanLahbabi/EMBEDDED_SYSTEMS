#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "memoire_24.h"

const uint8_t LONGUEUR_CHAINE = 46;
const uint8_t DEBUT_CHAINE = 0x00;
uint8_t CHAINE[LONGUEUR_CHAINE] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";

void allumerVert()
{
    PORTA = (1 << PA1);
}
void allumerRouge()
{
    PORTA = (1 << PA0);
}



bool validation(uint8_t* chaineAValider, uint8_t longueurChaine)
{
    bool pareil = true;

    for (uint8_t i = 0; i < longueurChaine; i++)
    {
        pareil &= CHAINE[i] == chaineAValider[i];
    }
    return pareil;
}


int main()
{
    DDRA |= (0xff);
    Memoire24CXXX memoire;
    uint8_t chaineEnMemoire[LONGUEUR_CHAINE];

    memoire.ecriture(DEBUT_CHAINE, &CHAINE[0], LONGUEUR_CHAINE);
    _delay_ms(5);
    memoire.lecture(DEBUT_CHAINE, &chaineEnMemoire[0], LONGUEUR_CHAINE);

    if (validation(chaineEnMemoire, LONGUEUR_CHAINE))
        allumerVert();

    else
        allumerRouge();

}

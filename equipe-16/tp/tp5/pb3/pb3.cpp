#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "memoire_24.h"

Memoire24CXXX memoire;

void allumerVert()
{
    PORTA = (1 << PA1);
}
void allumerRouge()
{
    PORTA = (1 << PA0);
}


/*
Vous devrez faire un programme qui écrit la chaîne de caractères « *P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*»
suivi d'un 0x00 en mémoire externe du ATmega324PA. La chaîne commencera à l'adresse 0x0000 (sur 16 bits, donc).
Faire en sorte que votre programme puisse aller relire la chaîne en question. Comparez la chaîne de caractères envoyée à la mémoire
et celle relue. Il suffira de faire afficher une DEL en vert si elles sont identiques et en rouge dans le cas contraire.
Utiliser les ports que vous voulez pour connecter cette DEL. Cette démarche est un peu douteuse au départ, mais elle se raffinera
avec le problème 3. Il faut prévoir un délai de 5 ms après l'écriture d'un octet en mémoire et l'accès suivant à la mémoire.
De cette façon, la mémoire peut compléter son cycle d'écriture sans problème. Aucun besoin d’utiliser le RS232 ici.
On veut simplement maîtriser la mémoire externe dans un premier temps.
*/

const uint8_t LONGUEUR_CHAINE = 46;
uint8_t CHAINE[LONGUEUR_CHAINE] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
const uint16_t DEBUT_CHAINE = 0x00;

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

    _delay_ms(5000);
    memoire.ecriture(DEBUT_CHAINE, &CHAINE[0], LONGUEUR_CHAINE);
    ///memoire.ecriture(DEBUT_CHAINE + LONGUEUR_CHAINE * sizeof(uint8_t), 0xFF);

    uint8_t chaineEnMemoire[LONGUEUR_CHAINE];
    memoire.lecture(DEBUT_CHAINE, &chaineEnMemoire[0], LONGUEUR_CHAINE);


    if (validation(chaineEnMemoire, LONGUEUR_CHAINE))
    {
        allumerVert();
    }
    else
    {
        allumerRouge();
    }
}

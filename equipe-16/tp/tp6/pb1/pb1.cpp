/*
Travail : TRAVAIL_PRATIQUE 6, Problème 1
Section # : 01
Équipe # : EQUIPE_NO 16
Auteurs : Ryan Lahbabi , Ali Mouchahid
Correcteur : Charles

Description du programme: Le programme ci-dessous répond au problème 1.
Ce porgramme permet de compiler sur un microprocesseur atmega 324
qui incrémente un compteur 10 fois par seconde et change le comportement d'une LED en fonction du bouton poussoir blanc sur le breadboard.
Le programme  contrôle la del  par demande d'interruption externe 0 (INT0_vect) en connectant le signal de sortie au port PD2 de la carte mere.
Nous avons fais clignoter la DEL dépendamment de la valeur du compteur engendrer par l'appuie du bouton poussoir.
Afin de traiter le problème de debounce, nous avons inclus un délais anti_rebond de 30 ms dans la fonction ISR de l'interruption du Boutton.

Identifications matérielles (Broches I/O):
INT 0/1: PD2; DDRD --> Ces input prennent comme valeur 0 ou 1 afin de savoir si le courant passe ou non.
Analog Digital Converter: PB0; PB1; DDRB --> Ces Output ressort le courant conduit par le bouton poussoir Blanc .
PB0 ressort le courant afin d'allumer la DEL bicoolore en vert et PB1 allume la DEL bicolore en rouge
On réfère PD2 au bouton poussoir blanc sur le breadboard.
*/

//
// +────────────────+───────────────────────────────────+──────────────────+─────────────────────── +
// | Etat Courant   |  Scenario                         | Etat Suivant     | Output                 |
// +────────────────+────────────────────────────────── +───────────────── +─────────────────────── +
// | INIT           | Compteur < 120 ou Bouton relacher | CLIGNOTER_VERT   | Del eteinte            |
// | CLIGNOTER_VERT | minuterie de 1/2 seconde          | CLIGNOTER_ROUGE  | Del clignotant vert    |
// | CLIGNOTER_ROUGE| Iterer compteurFinal / 2 fois     | VERT             | Del clignotant Rouge   |
// | VERT           | delay de 1 seconde                | INIT             | Del verte              |
// +────────────────+────────────────────────────────── +───────────────── +────────────────────────+

#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>

volatile uint8_t boutonRelacher = 0;
volatile uint8_t compteur = 0;
volatile uint8_t minuterieExpiree = 0;

const uint8_t COMPTEUR_MAX = 120;
const uint8_t INPUT_VALEUR = 0x00;

// Ces valeurs correspondent aux nombre d'introductions par seconde si on divise la clock par le prescaler de 1024.
const uint16_t DEMI_SECONDE = 2604;
const uint16_t DIXIEME_DE_SECONDE = 781;

const uint8_t ANTI_REBOND = 30;
// Les trois valeurs suivantes sont les valeurs des secondes en milisecondes.
const uint8_t MILLIEME_DE_SECONDE = 1;
const uint8_t QUART_DE_SECONDE = 250;
const uint16_t UNE_SECONDE = 1000;
const uint16_t DEUX_SECONDE = 2000;

enum class Etat
{
    INIT,
    CLIGNOTER_VERT,
    CLIGNOTER_ROUGE,
    VERT
};

Etat etatCourant = Etat::INIT;

void allumerVert()
{
    PORTB |= (1 << PB0);
}
void allumerRouge()
{
    PORTB |= (1 << PB1);
}

void eteindre()
{
    PORTB &= (1 << PB1) & (1 << PB0);
}

void minuterie(uint16_t duree)
{
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A = _BV(COM1A0);

    TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);
    
    TCCR1C = 0;

    TIMSK1 = _BV(OCIE1A);

    minuterieExpiree = 0;
}

void initialisationInt(void)
{

    cli();
    DDRB |= _BV(PORTB0) | _BV(PORTB1);
    DDRD &= INPUT_VALEUR;
    EIMSK |= _BV(INT0);

    EICRA = _BV(ISC00);

    sei();
}

ISR(TIMER1_COMPA_vect)
{
    compteur++;
    minuterieExpiree = 1;
}

ISR(INT0_vect)
{
    _delay_ms(ANTI_REBOND);
    boutonRelacher = !boutonRelacher;
}

uint8_t etatInitial(Etat &etatCourant)
{
    eteindre();
    uint8_t compteurFinal = 0;
    compteur = 0;

    if (boutonRelacher)
    {
        minuterie(DIXIEME_DE_SECONDE);

        while (boutonRelacher && compteur < COMPTEUR_MAX)
            ;
        compteurFinal = compteur;
        etatCourant = Etat::CLIGNOTER_VERT;
    }
    return compteurFinal;
}

void etatClignoterVert(Etat &etatCourant)
{
    minuterie(DEMI_SECONDE);
    while (!minuterieExpiree)
    {
        allumerVert();
        _delay_ms(MILLIEME_DE_SECONDE);
        eteindre();
        _delay_ms(MILLIEME_DE_SECONDE);
    }
    etatCourant = Etat::CLIGNOTER_ROUGE;
}

void etatClignoterRouge(Etat &etatCourant, uint8_t compteurFinal)
{
    _delay_ms(DEUX_SECONDE);
    for (uint8_t i = 0; i < compteurFinal / 2; i++)
    {
        allumerRouge();
        _delay_ms(QUART_DE_SECONDE);
        eteindre();
        _delay_ms(QUART_DE_SECONDE);
    }
    etatCourant = Etat::VERT;
}

void etatVert(Etat &etatCourant)
{
    allumerVert();
    _delay_ms(UNE_SECONDE);
    boutonRelacher = 0;
    etatCourant = Etat::INIT;
}

int main()
{
    initialisationInt();
    uint8_t compteurFinal = 0;

    while (true)
    {
        switch (etatCourant)
        {
        case Etat::INIT:
            compteurFinal = etatInitial(etatCourant);
            break;

        case Etat::CLIGNOTER_VERT:
            etatClignoterVert(etatCourant);
            break;

        case Etat::CLIGNOTER_ROUGE:
            etatClignoterRouge(etatCourant, compteurFinal);
            break;

        case Etat::VERT:
            etatVert(etatCourant);
            break;
        }
    }
}

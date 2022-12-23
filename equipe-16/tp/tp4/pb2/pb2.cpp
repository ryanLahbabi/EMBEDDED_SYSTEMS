#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>

const int ANTI_REBOND = 40;

const void eteindre(){
     
    PORTA &= ~((1 << PA1) | (1<<PA0));
}

const void allumerVert(){
    PORTA = (1 << PA1);
}

const void allumerRouge(){
    PORTA = (1 << PA0);
}

enum class Etat{
ATTENTE, 
CLIGNOTER,
ETEINT,
VERT,
ROUGE
};

volatile uint8_t gMinuterieExpiree;
volatile uint8_t gBoutonPoussoir;

Etat etatCourant = Etat::ATTENTE;



ISR (INT0_vect) {
    _delay_ms(ANTI_REBOND);
    gBoutonPoussoir = 1;
    EIFR |= (1 << INTF0); // re-enable interruption

}

ISR (TIMER1_COMPA_vect) {

    gMinuterieExpiree = 1;
}



void partirMinuterie ( uint16_t duree ) { //value to give : 7813 hz

    gMinuterieExpiree = 0;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0; // Pour toutes les lignes suivantes le 1 correspond a la minutrie de 16 bits. 
    OCR1A = duree;

    TCCR1A = 0;//0 << WGM10 | 0 << WGM11   registre flag d interruption 

    TCCR1B |= (1 << CS12) | (1 << CS10) ; // division de la clock par 1024

    TCCR1C = 0; // wave forme

    TIMSK1 |= 1 << OCIE1A ; // mode de comparaison entre clock et duree

}

void initialisation(void)
{

    cli(); // section protegee anti interruption

        DDRA |= 0xff; //OUTPUTS
        DDRD &= 0x00; //INPUTS

        EIMSK |= (1 << INT0); //interruption sur bouton d2

        EICRA |= (1 << ISC00) | (1<< ISC01) ; // falling edge btn d2
    

    sei();
}

void gererDel()
{ 
     
    switch (etatCourant)
        {
        case Etat::ATTENTE:
            _delay_ms(10000);
            etatCourant = Etat::CLIGNOTER;
            break;

        case Etat::CLIGNOTER:
            allumerRouge();
            _delay_ms(100);
            etatCourant = Etat::ETEINT;
            break;  

        case Etat::ETEINT:
            eteindre();
            partirMinuterie(7813);
            do{
            // attendre qu'une des deux variables soit modifiée
            // par une ou l'autre des interruptions.
            } while ( gMinuterieExpiree == 0 && gBoutonPoussoir == 0 );
            // Une interruption s'est produite. Arrêter toute
            // forme d'interruption. Une seule réponse suffit.
            
            cli ();

            // Verifier la réponse
            if(gBoutonPoussoir)
                etatCourant = Etat::VERT;
            else if(gMinuterieExpiree)   
                etatCourant = Etat::ROUGE;
   
            break;
        case Etat::VERT:
            allumerVert();
            break;
        case Etat::ROUGE:
            allumerRouge();
    }
}
        
        




int main()
{
    initialisation();
    while(true)
    {  
        gererDel();
      
}
}


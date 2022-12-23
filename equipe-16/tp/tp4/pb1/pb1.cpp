#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>

const int DELAIS_ANTIREBOND = 10;
const int DELAIS_AMBRE_ROUGE = 1;
const int DELAIS_AMBRE_VERT = 5;

enum class Etat
{
    ETEINT,
    ROUGE,
    VERT,
    AMBRE,
    ROUGE_2, 
    VERT_2
};

volatile bool gBtnAppuye = false;
Etat etatCourant = Etat::ROUGE;

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
    while(gBtnAppuye == true)
    {allumerVert();
    _delay_ms(DELAIS_AMBRE_VERT);
    allumerRouge();
    _delay_ms(DELAIS_AMBRE_ROUGE);
    }
}


void initialisation(void)
{

    cli();

    DDRA |= 0xff;
    DDRD &= 0x00;
    EIMSK |= (1 << INT0);

    EICRA |= (1 << ISC00) | (0 << ISC01)  ;
  

    sei();
}

ISR(INT0_vect)
{
    _delay_ms(40);
    gBtnAppuye = !gBtnAppuye;
    EIFR |= (1 << INTF0);
}

void gererDel()
{ 
     
        switch (etatCourant)
            {
            case Etat::ROUGE:

                allumerRouge();
                if (gBtnAppuye) etatCourant = Etat::AMBRE;
                break;

            case Etat::AMBRE:
                allumerAmbre();
                if (!gBtnAppuye) etatCourant = Etat::VERT;
                break;

            case Etat::VERT:
                allumerVert();
                if (gBtnAppuye) etatCourant = Etat::ROUGE_2;
                break;

            case Etat::ROUGE_2:
                allumerRouge();
                if (!gBtnAppuye) etatCourant = Etat::ETEINT;
                break; 

            case Etat::ETEINT:
                eteindre();
                if (gBtnAppuye) etatCourant = Etat::VERT_2;
                break; 
        
            case Etat::VERT_2:
                allumerVert();
                if (!gBtnAppuye) etatCourant = Etat::ROUGE;
                break; 
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
    

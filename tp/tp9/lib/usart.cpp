#include <usart.h>

void Usart::initialiser()

{

    UBRR0H = 0;

    UBRR0L = 0xCF;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (1 << USBS0) | (3 << UCSZ00);

}

void Usart::transmettreCaractere(const char caractere)

{

    while (!(UCSR0A & (1 << UDRE0)))

        ;

    UDR0 = caractere;

}

void Usart::transmettreChaineCaractere(const char *caracteres)

{

    uint8_t index = 0;

    while (caracteres[index] != '\0')

    {

        transmettreCaractere(caracteres[index]);

        index++;

    }

};

void Usart::transmettreEntier8bits (uint8_t donnees) {

    char temp[10];

    sprintf(temp, "%d", donnees);

    transmettreChaineCaractere(temp);

}

uint8_t Usart::recevoirCaractere()

{

     while (!(UCSR0A & (1 << RXC0)))

        ;

    return UDR0;

}

#include <afficher.h>


Afficher::Afficher()
{
    USART_Init();
}

void Afficher::USART_Init()
{

    UBRR0H = 0;

    UBRR0L = 0xCF;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

/**
 * @brief Transmet un caracère à l'ordinateur
 * 
 * @param caractere 
 */
void Afficher::afficherCaractere(const char caractere)
{

    while (!(UCSR0A & (1 << UDRE0)))
        ;

    UDR0 = caractere;
}

/**
 *
 * @brief transmet les caractères de la chaine à l'ordinateur
 * 
 * @param caracteres : chaine de caractères
 */
void Afficher::afficherChaineCaractere(const char *caracteres)
{
    uint8_t index = 0;

    while (caracteres[index] != '\0')
    {
        afficherCaractere(caracteres[index]);
        index++;
    }
};

/**
 * @brief Lit un caractère qui vient de l'ordianteur
 * 
 * @return uint8_t 
 */
uint8_t Afficher::lireCaractere()
{
    while (!((UCSR0A) & (1 << RXC0)))
        ;

    return UDR0;
}
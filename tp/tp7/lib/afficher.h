#include <avr/io.h>
#include <avr/interrupt.h>
#include <memoire_24.h>
#include <stdio.h>

class Afficher
{
public:
  Afficher();

 void USART_Init();

 void afficherCaractere( const char caractere);

 void afficherChaineCaractere(const char *caracteres);

unsigned char lireCaractere( void );

};
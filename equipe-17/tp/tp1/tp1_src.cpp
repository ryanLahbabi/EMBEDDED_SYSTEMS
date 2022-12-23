/*
 * Nom: tp1_src
 * Copyright (C) 2022 Evan BLANC / Ahmed ZGAHL
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: L'exercice consiste à faire allumer la DEL de chaque couleur pour quelques secondes. On affichera d'abord la couleur rouge, puis la couleur verte puis la couleur ambrée. On répétera cette séquence à l'infini.
 * Version: 1.1
 */

#define F_CPU 8000000U
#include <avr/io.h>
#include <util/delay.h>

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff; // PORT D est en mode sortie

  for(;;)  // boucle sans fin
  {
      PORTA = 0X01;
      _delay_ms(1000);
      PORTA = 0X02;
  }
  return 0; 
}

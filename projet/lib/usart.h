#pragma once

#include <avr/io.h>

#include <avr/interrupt.h>

#include <memoire_24.h>

#include <stdio.h>

class Usart

{

public:

  /**
   * @brief Initisalise les registres nécéssaires à la transmition USART
   */

  static void initialiser();

  /**
   * @brief Transmet un caractère
   * 
   * @param char caractere
   */

  static void transmettreCaractere( const char caractere);

  /**
   * @brief Transmet une chaine de caractères grâce à Usart::transmettreCaractere()
   * 
   * @param char* caracteres
   */

  static void transmettreChaineCaractere(const char *caracteres);

  /**
   * @brief Transmet un entier 8bits grâce à Usart::transmettreCaractere()
   * 
   * @param char caractere
   */

  static void transmettreEntier8bits (uint8_t donnees);

  /**
   * @brief Transmet un entier 16bits grâce à Usart::transmettreCaractere()
   * 
   * @param char caractere
   */
  static void transmettreEntier16bits (uint16_t donnees);
  /**

   * @brief Recoit un octet
   * 
   * @return uint8_t l'octet reçu
   */

  static uint8_t recevoirCaractere();

};

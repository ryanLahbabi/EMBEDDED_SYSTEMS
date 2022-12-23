#include "chargementMemoireExterne.h"

ChargementMemoireExterne::ChargementMemoireExterne() : _memoire(), _nbTotalOctets(0x0000) {}

void ChargementMemoireExterne::ecritureDonnees() {
    Usart::initialiser();
    uint8_t premierOctet = static_cast<uint8_t>(Usart::recevoirCaractere());
    uint8_t deuxiemeOctet = static_cast<uint8_t>(Usart::recevoirCaractere());
    uint8_t donnee;

    _nbTotalOctets |=( premierOctet << 0x08 | deuxiemeOctet) ;

    _memoire.ecriture(0x0000, static_cast<const uint8_t>(premierOctet));
    _delay_ms(5);
    _memoire.ecriture(0x0001, static_cast<const uint8_t>(deuxiemeOctet));
    _delay_ms(5);

    for (uint16_t i = 2; i < _nbTotalOctets; i++) {
        donnee = Usart::recevoirCaractere();
        _memoire.ecriture(0x0000 + i, donnee);
        _delay_ms(5);
    }
}
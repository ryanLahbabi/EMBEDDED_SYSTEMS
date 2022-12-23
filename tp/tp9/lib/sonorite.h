#pragma once
#include <avr/io.h>

class Sonorite {
    public:
        static void jouerNote(uint8_t note);
        static void arreter();
		static const uint16_t notes[37];
};
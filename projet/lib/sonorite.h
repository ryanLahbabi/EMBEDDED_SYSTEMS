#pragma once
#include <avr/io.h>

enum class Note {
    GRAVE = 50,
    AIGU = 70,
};

class Sonorite {
    public:
        static void jouerNote(Note note);
        static void arreter();
		static const uint16_t notes[37];
};
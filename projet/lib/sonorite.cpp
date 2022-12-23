#include "sonorite.h"
#ifndef F_CPU
#define F_CPU 8000000
#endif

const uint16_t Sonorite::notes[] = {
	4545,
	4290,
	4050,
	3822,
	3608,
	3405,
	3214,
	3034,
	2863,
	2703,
	2551,
	2408,
	2273,
	2145,
	2025,
	1911,
	1804,
	1703,
	1607,
	1517,
	1432,
	1351,
	1276,
	1204,
	1136,
	1073,
	1012,
	956,
	902,
	851,
	804,
	758,
	716,
	676,
	638,
	602,
	568
};

void Sonorite::jouerNote(Note note) {
	DDRD |= (1 << PD5) | (1 << PD4);
    TCCR1B |= (1 << CS11) | (1 << WGM12);
    TCCR1A |= (1 << COM1A0);
    OCR1A = notes[static_cast<uint8_t>(note) - 45];
    TCNT1 = 0x0000;
}

void Sonorite::arreter() {
    TCCR1A &= ~((1 << COM1A0) | (1 << COM1A1));
    OCR1A = 0x0000;
}
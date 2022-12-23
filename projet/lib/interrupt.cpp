#include <interrupt.h>

/**
 * @brief implémente l'interruption du boutton
 * 
 * @param id : INT0 - INT1 - INT2
 * @param mode : ModeInterruption enum class 
 **/
void BoutonInterruption::initialiser(uint8_t id, ModeInterruption mode) {
    cli();

    EIMSK |= _BV(id);

    switch (mode) {
        case ModeInterruption::LowLevelInterrupt:
            EICRA &= ~(_BV(ISC00)| _BV(ISC01));
            break;

        case ModeInterruption::AnyEdgeInterrupt:
            EICRA |= _BV(ISC00);
            EICRA &= ~_BV(ISC01);
            break;

        case ModeInterruption::FallingEdgeInterrupt:      
            EICRA &= ~_BV(ISC00);
            EICRA |= _BV(ISC01);
            break;

        case ModeInterruption::RisingEdgeInterrupt:
            EICRA |= _BV(ISC00) | _BV(ISC01);
            break;
    }

    sei();
}
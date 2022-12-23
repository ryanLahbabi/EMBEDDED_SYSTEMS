#include <avr/interrupt.h>

enum class ModeInterruption {
        LowLevelInterrupt,
        AnyEdgeInterrupt,
        FallingEdgeInterrupt,
        RisingEdgeInterrupt
    };


namespace BoutonInterruption {
    void initialiser(uint8_t id, ModeInterruption mode);
};
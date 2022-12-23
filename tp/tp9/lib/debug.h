#pragma once
#include <usart.h>

#ifdef DEBUG
# define DEBUG_PRINT(x) Usart::transmettreChaineCaractere(x)
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif



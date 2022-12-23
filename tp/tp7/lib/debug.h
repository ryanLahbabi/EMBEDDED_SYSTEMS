#pragma once
#include <afficher.h>

Afficher print;


#ifdef DEBUG
# define DEBUG_PRINT(x) print.afficherChaineCaractere(x)
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif



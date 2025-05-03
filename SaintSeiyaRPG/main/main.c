#include <stdio.h>
#include <stdlib.h>

#include "../Knight/knights.h"

int main() {
    Knight party[MAX_KNIGHTS];
    initialize_knights(party);

    // Ejemplo: Combate Seiya vs Shiryu
    print_knight_stats(&party[0]); // Stats de Seiya
    print_knight_stats(&party[1]); // Stats de Shiryu
    execute_attack(&party[0], 0, &party[1]); // Ataque básico
    printf("\nShiryu HP after attack: %d\n", party[1].hp);

    return 0;
}
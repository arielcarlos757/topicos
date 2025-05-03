#include "knights.h"
#include <stdio.h>
#include <string.h>

// Inicializa los 5 caballeros con stats base
void initialize_knights(Knight party[]) {
    Knight seiya = {
        "Seiya", PEGASUS, 100, 50, 20, 10,
        {"Meteoro de Pegaso", "Cometa de Pegaso", "Final de Pegaso"}, 1
    };
    Knight shiryu = {
        "Shiryu", DRAGON, 120, 60, 18, 15,
        {"Dragón Naciente", "Cólera del Dragón", "Excalibur"}, 1
    };
    Knight hyoga = {
        "Hyoga", CYGNUS, 90, 70, 15, 12,
        {"Polvo de Diamantes", "Ejecución de Aurora", "Tornado de Aurora"}, 1
    };
    Knight shun = {
        "Shun", ANDROMEDA, 80, 80, 12, 8,
        {"Cadena de Andrómeda", "Tormenta Nebular", "Defensa Circular"}, 1
    };
    Knight ikki = {
        "Ikki", PHOENIX, 150, 40, 25, 20,
        {"Golpe del Fénix", "Ilusión del Fénix", "Renacer del Fénix"}, 1
    };

    party[0] = seiya;
    party[1] = shiryu;
    party[2] = hyoga;
    party[3] = shun;
    party[4] = ikki;
}

// Muestra las stats de un caballero
void print_knight_stats(const Knight *knight) {
    printf("\n=== %s ===\n", knight->name);
    printf("HP: %d\nCosmos: %d\n", knight->hp, knight->cosmos);
    printf("Ataques especiales:\n");
    for (int i = 0; i < MAX_ATTACKS; i++) {
        printf("- %s\n", knight->special_attacks[i]);
    }
}

// Ejecuta un ataque y devuelve el daño infligido
int execute_attack(const Knight *attacker, int attack_index, Knight *defender) {
    if (attack_index < 0 || attack_index >= MAX_ATTACKS) return 0;

    int damage = attacker->attack_power;
    // Ataques especiales consumen cosmos
    if (attack_index > 0 && attacker->cosmos >= 20) {
        damage *= 2; // Doble daño para ataques especiales
        defender->cosmos -= 20;
    }

    defender->hp -= (damage - defender->defense);
    return damage;
}

// Restaura cosmos (usado entre combates)
void restore_cosmos(Knight *knight, int amount) {
    knight->cosmos += amount;
    if (knight->cosmos > 100) knight->cosmos = 100;
}

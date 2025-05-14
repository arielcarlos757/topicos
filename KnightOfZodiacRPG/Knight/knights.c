//
// Created by dev on 9/05/25.
//
#include "knights.h"
#include <stdio.h>
#include <string.h>

// Inicializa los 5 caballeros con stats base
void initialize_knights(Knight party[]) {
    Knight seiya = {
        "Seiya", PEGASUS, 100, 50, 20000, 1000,
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

void initialize_golden_knights(Knight golden_knights[]) {
    // Aries Mu
    golden_knights[0] = (Knight){
        "Mu", ARIES, 300, 150, 25, 30,
        {"Muro de Cristal", "Extinción Estelar", "Regeneración"}, 1
    };

    // Taurus Aldebarán
    golden_knights[1] = (Knight){
        "Aldebarán", TAURUS, 350, 100, 40, 35,
        {"Gran Cuerno", "Tierra Embiste", "Piel de Diamante"}, 1
    };

    // Gemini Saga/Kanon
    golden_knights[2] = (Knight){
        "Saga", GEMINI, 400, 200, 35, 25,
        {"Explosión Galáctica", "Otra Dimensión", "Ilusión Demoníaca"}, 1
    };

    // Cancer Deathmask
    golden_knights[3] = (Knight){
        "Deathmask", CANCER, 280, 120, 30, 20,
        {"Ondas del Inframundo", "Viaje a los Muertos", "Escudo de Almas"}, 1
    };

    // Leo Aioria
    golden_knights[4] = (Knight){
        "Aioria", LEO, 380, 180, 45, 28,
        {"Relámpago de Plasma", "Garras del León", "Coraza Solar"}, 1
    };

    // Virgo Shaka
    golden_knights[5] = (Knight){
        "Shaka", VIRGO, 420, 250, 30, 40,
        {"Tesoro del Cielo", "Om", "Ilusión de Buda"}, 1
    };

    // Libra Dohko
    golden_knights[6] = (Knight){
        "Dohko", LIBRA, 370, 170, 38, 32,
        {"Cólera del Dragón", "Ataque de las 100 Montañas", "Armadura Dorada"}, 1
    };

    // Scorpio Milo
    golden_knights[7] = (Knight){
        "Milo", SCORPIO, 360, 160, 33, 27,
        {"Aguja Escarlata", "Pica de Antares", "Golpe de Cola"}, 1
    };

    // Sagittarius Aioros
    golden_knights[8] = (Knight){
        "Aioros", SAGITTARIUS, 390, 190, 42, 30,
        {"Flecha de Sagitario", "Torbellino de Estrellas", "Alas Doradas"}, 1
    };

    // Capricorn Shura
    golden_knights[9] = (Knight){
        "Shura", CAPRICORN, 375, 175, 48, 35,
        {"Excalibur", "Corte Sagrado", "Piel de Adamantium"}, 1
    };

    // Aquarius Camus
    golden_knights[10] = (Knight){
        "Camus", AQUARIUS, 365, 200, 36, 29,
        {"Ejecución de Aurora", "Círculo de Hielo", "Templo del Frío"}, 1
    };

    // Pisces Aphrodite
    golden_knights[11] = (Knight){
        "Aphrodite", PISCES, 340, 140, 32, 22,
        {"Rosas Sangrientas", "Rosas Pirañas", "Fragancia Mortal"}, 1
    };
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

// Devuelve:
//   1 si el atacante gana,
//  -1 si el defensor gana,
//   0 si el combate continúa
int determine_winner(const Knight *attacker, const Knight *defender) {
    // Caso 1: Defensor derrotado (HP <= 0)
    if (defender->hp <= 0) {
        printf("\n¡%s ha derrotado a %s!\n", attacker->name, defender->name);
        return 1;
    }

    // Caso 2: Atacante derrotado (HP <= 0)
    if (attacker->hp <= 0) {
        printf("\n¡%s ha caído en batalla!\n", attacker->name);
        return -1;
    }

    // Caso 3: Empate (ambos con HP <= 0)
    if (attacker->hp <= 0 && defender->hp <= 0) {
        printf("\n¡Doble KO! Ambos caballeros han caído.\n");
        return 0;
    }

    // Caso 4: Combate continúa (ambos con HP > 0)
    return 0;
}

// Restaura cosmos (usado entre combates)
void restore_cosmos(Knight *knight, int amount) {
    knight->cosmos += amount;
    if (knight->cosmos > 100) knight->cosmos = 100;
}
Knight* get_enemy(const int enemy) {
    return NULL;
}
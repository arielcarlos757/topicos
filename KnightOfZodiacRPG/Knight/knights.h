//
// Created by dev on 9/05/25.
//

#ifndef KNIGHTS_H
#define KNIGHTS_H

#define MAX_KNIGHTS 5
#define MAX_GOLDEN_KNIGHTS 12
#define MAX_ATTACKS 3

// Tipos de caballeros (para habilidades especiales)
typedef enum {
    PEGASUS, DRAGON, CYGNUS, ANDROMEDA, PHOENIX,
    ARIES, TAURUS, GEMINI, CANCER, LEO, VIRGO,
    LIBRA, SCORPIO, SAGITTARIUS, CAPRICORN, AQUARIUS, PISCES
} KnightType;

// Estructura de un caballero
typedef struct {
    char name[20];          // Ej: "Seiya"
    KnightType type;        // Tipo (usado para habilidades)
    int hp;                 // Salud (100 = máximo)
    int cosmos;             // Energía para ataques especiales (0-100)
    int attack_power;       // Daño base
    int defense;            // Reducción de daño
    char special_attacks[MAX_ATTACKS][50]; // Nombres de ataques
    int is_alive;           // 1 si está vivo, 0 si fue derrotado
} Knight;

// Prototipos de funciones
void initialize_knights(Knight party[]);
void initialize_golden_knights(Knight golden_knights[]);
void print_knight_stats(const Knight *knight);
int execute_attack(const Knight *attacker, int attack_index, Knight *defender);
void restore_cosmos(Knight *knight, int amount);
int determine_winner(const Knight *attacker, const Knight *defender);
#endif //KNIGHTS_H

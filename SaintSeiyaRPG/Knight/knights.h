#ifndef KNIGHTS_H_INCLUDED
#define KNIGHTS_H_INCLUDED

#define MAX_KNIGHTS 5
#define MAX_ATTACKS 3

// Tipos de caballeros (para habilidades especiales)
typedef enum {
    PEGASUS, DRAGON, CYGNUS, ANDROMEDA, PHOENIX
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
void print_knight_stats(const Knight *knight);
int execute_attack(const Knight *attacker, int attack_index, Knight *defender);
void restore_cosmos(Knight *knight, int amount);

#endif // KNIGHTS_H_INCLUDED

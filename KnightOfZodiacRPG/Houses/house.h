//
// Created by dev on 11/05/25.
//

#ifndef HOUSE_H
#define HOUSE_H

#define NUM_HOUSES 12


typedef struct {
    char name[50];        // Ej: "Casa de Aries"
    char description[200]; // Descripción atmosférica
    int enemy_id;         // ID del Caballero Dorado (índice en golden_knights[])
    int next_house;       // Casa siguiente (índice)
    int is_boss;          // 1 si es la casa final (Sagitario/Géminis)
} House;

// Primitivas principales
void house_initialize_all(House houses[]);
House* house_get_by_id(House houses[], int id);
int house_is_final(House* house);
const char* house_get_enemy_name(House* house);

#endif //HOUSE_H

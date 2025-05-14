//
// Created by dev on 11/05/25.
//
#include "house.h"
#include <stddef.h>
#include "../Knight/knights.h"

void house_initialize_all(House houses[]) {
    houses[ARIES] = (House){
        "Casa de Aries",
        "Un templo rodeado de cristales que reflejan el cosmos.",
        0,  // Mu de Aries
        TAURUS,
        0
    };

    houses[TAURUS] = (House){
        "Casa de Tauro",
        "Un coliseo de piedra con marcas de gigantescos cuernos.",
        1,  // Aldebarán
        GEMINI,
        0
    };

    houses[GEMINI] = (House){
        "Casa de Géminis",
        "Un laberinto dimensional que cambia constantemente.",
        2,  // Saga
        CANCER,
        1   // Casa jefe
    };

    houses[CANCER] = (House){
        "Casa de Cancer",
        "Mascara mortal.",
        2,  // Saga
        LEO,
        0   // Casa jefe
    };

    houses[LEO] = (House){
        "Casa de Leo",
        "Aioria, el leon.",
        2,  // Saga
        VIRGO,
        0   // Casa jefe
    };

    houses[VIRGO] = (House){
        "Casa de Virgo",
        "Shakka, el mas cercano al gran maestro.",
        2,  // Saga
        LIBRA,
        0   // Casa jefe
    };

    houses[LIBRA] = (House){
        "Casa de Libra",
        "La armadura de Libra.",
        2,  // Saga
        SCORPIO,
        0   // Casa jefe
    };

    houses[SAGITTARIUS] = (House){
        "Casa de Sagitario",
        "El legado de Aioros.",
        2,  // Saga
        CAPRICORN,
        0   // Casa jefe
    };

    houses[CAPRICORN] = (House){
        "Casa de Capricornio",
        "Excalibur.",
        2,  // Saga
        AQUARIUS,
        0   // Casa jefe
    };

    houses[AQUARIUS] = (House){
        "Casa de Acuario",
        "Camus, el cero absoluto.",
        2,  // Saga
        PISCES,
        0   // Casa jefe
    };

    // ... Completa las 12 casas
    houses[PISCES] = (House){
        "Casa de Piscis",
        "Un jardín de rosas venenosas que emanan niebla dorada.",
        11,  // Afrodita
        -1,  // Fin del santuario
        0
    };
}

House* house_get_by_id(House houses[], int id) {
    if (id >= 0 && id < NUM_HOUSES) {
        return &houses[id];
    }
    return NULL;
}

int house_is_final(House* house) {
    return house->is_boss;
}

const char* house_get_enemy_name(House* house) {
    /*// Asume que golden_knights[] está inicializado
     Knight golden_knights[]; por ahora no lo usamos
    if (house->enemy_id >= 0) {
        return golden_knights[house->enemy_id].name;
    }*/
    return "Ninguno";
}
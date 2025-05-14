#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para sleep()

#include "Houses/house.h"
#include "Knight/knights.h"
#include "Story/story.h"

// Función para limpiar la pantalla (multi-plataforma)
void clear_screen() {
    /*
    system("clear || cls");
*/
    system("clear");
}

// Muestra el logo ASCII de Saint Seiya
void show_logo() {
    clear_screen();
    printf("\033[1;33m"); // Color amarillo brillante
    printf("   _____      _       _   _____       _       _          \n");
    printf("  / ____|    | |     | | |_   _|     (_)     | |   /\\    \n");
    printf(" | (___   ___| |_ ___| |_  | |  _ __  _  __ _| |  /  \\   \n");
    printf("  \\___ \\ / _ \\ __/ __| __| | | | '_ \\| |/ _` | | / /\\ \\  \n");
    printf("  ____) |  __/ || (__| |_ _| |_| | | | | (_| | |/ ____ \\ \n");
    printf(" |_____/ \\___|\\__\\___|\\__|_____|_| |_|\\__,_|_/_/    \\_\\\n\n");
    printf("\033[0m"); // Resetear color
}

// Menú principal con validación de entrada
int main_menu() {
    int choice = 0;
    do {
        show_logo();
        printf("\n=== SANTUARIO RPG ===\n");
        printf("\033[1;36m1. Nueva Partida\033[0m\n");
        printf("\033[1;32m2. Cargar Partida\033[0m\n");
        printf("\033[1;31m3. Salir\033[0m\n\n> ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Limpiar buffer de entrada
            printf("\033[1;31mError: Ingresa un número válido.\033[0m\n");
            sleep(1);
        }
    } while (choice < 1 || choice > 3);

    return choice;
}

// Cinemática de inicio (texto animado)
void intro_cinematic() {
    clear_screen();
    printf("\033[1;34m");
    const char *message = "El Santuario, bajo el control del Patriarca impostor (Saga de Géminis), es un laberinto de desafíos cósmicos.\nAthena ha sido herida por una flecha dorada, y su vida pende de un hilo. \nSeiya (el jugador) y sus compañeros deben superar las Doce Casas del Zodíaco, custodiadas por los Caballeros de Oro, para alcanzar la Cámara del Patriarca y salvar a la diosa.\n";
    for (int i = 0; message[i]; i++) {
        putchar(message[i]);
        fflush(stdout);
        usleep(50000); // 50ms entre caracteres
    }
    sleep(2);
    printf("\033[0m");
}

void start_game() {
    Knight party[MAX_KNIGHTS];
    initialize_knights(party);

    printf("\n\033[3m\"El destino de Athena está en tus manos, caballero...\"\033[0m\n\n");
    sleep(2);
    // Aquí iría la lógica principal del juego
}

int main(void) {
    /*
    intro_cinematic();
    play_story_arc("../Assets/story/sanctuary_arc.txt");
    */
    Knight players[MAX_KNIGHTS];
    Knight golden_knigths[MAX_GOLDEN_KNIGHTS];
    House houses[MAX_GOLDEN_KNIGHTS];


    initialize_golden_knights(golden_knigths);
    initialize_knights(players);
    house_initialize_all(houses);
    house_initialize_all(houses);

    SceneNode* story = load_ternary_story("../Assets/story/sanctuary_arc_v2.txt");
    printf("\n¡Que el Cosmo te acompañe!\n");
    play_ternary_scene(story,houses, players, golden_knigths);
    //print_tree(story, 0);

    if (players[0].is_alive)
        printf("\n¡Haz vencido al patriarca!\n");
    else
        printf("\n¡Caballero caido!\n");

    free_ternary_tree(story);

    //start_game();
    printf("\n¡fin!\n");
    return 0;
}
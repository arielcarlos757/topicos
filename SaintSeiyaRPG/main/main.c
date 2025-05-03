#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para sleep()
#include "../Knight/knights.h"

// Función para limpiar la pantalla (multi-plataforma)
void clear_screen() {
    system("clear || cls");
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
    const char *message = "Hace años, la diosa Athena reencarnó como Saori Kido...\n";
    for (int i = 0; message[i]; i++) {
        putchar(message[i]);
        fflush(stdout);
        usleep(50000); // 50ms entre caracteres
    }
    sleep(2);
    printf("\033[0m");
}

// Bucle principal del juego
void start_game() {
    Knight party[MAX_KNIGHTS];
    initialize_knights(party);

    printf("\n\033[3m\"El destino de Athena está en tus manos, caballero...\"\033[0m\n\n");
    sleep(2);
    // Aquí iría la lógica principal del juego
}

int main() {
    int option;
    do {
        option = main_menu();

        switch(option) {
            case 1:
                intro_cinematic();
                start_game();
                break;
            case 2:
                // load_game();
                break;
        }
    } while (option != 3);

    printf("\n¡Que el Cosmo te acompañe!\n");
    return 0;
}

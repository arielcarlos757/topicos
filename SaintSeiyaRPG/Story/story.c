#include "story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void load_story(const char* filename, Scene scenes[], int* total_scenes) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir archivo de historia");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_TEXT_LENGTH];
    *total_scenes = 0;

    while (fgets(buffer, sizeof(buffer), file) && *total_scenes < MAX_SCENES) {
        if (strstr(buffer, "SCENE:")) {
            sscanf(buffer, "SCENE:%d", &scenes[*total_scenes].scene_id);

            // Leer diálogo (puede contener múltiples líneas)
            fgets(scenes[*total_scenes].dialogue, MAX_TEXT_LENGTH, file);

            // Leer opciones
            for (int i = 0; i < 3; i++) {
                if (fgets(buffer, MAX_TEXT_LENGTH, file)) {
                    if (strstr(buffer, "CHOICE:")) {
                        sscanf(buffer, "CHOICE:%d:%[^\n]",
                               &scenes[*total_scenes].next_scenes[i],
                               scenes[*total_scenes].choices[i]);
                    }
                }
            }
            (*total_scenes)++;
        }
    }
    fclose(file);
}

void display_scene(const Scene* scene) {
    printf("\n\033[1;35m=== Escena %d ===\033[0m\n", scene->scene_id);
    printf("\033[3m%s\033[0m\n", scene->dialogue); // Texto en itálica

    for (int i = 0; i < 3 && scene->choices[i][0] != '\0'; i++) {
        printf("\033[1;36m%d. %s\033[0m\n", i+1, scene->choices[i]);
    }
}

int get_user_choice() {
    int choice;
    printf("\n> ");
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("\033[1;31mOpción inválida. Ingresa 1-3:\033[0m ");
        while (getchar() != '\n'); // Limpiar buffer
    }
    return choice - 1; // Convertir a índice 0-based
}

void play_story_arc(const char* arc_file) {
    Scene scenes[MAX_SCENES];
    int total_scenes;

    load_story(arc_file, scenes, &total_scenes);

    int current_scene = 0;
    while (current_scene >= 0 && current_scene < total_scenes) {
        display_scene(&scenes[current_scene]);
        int choice = get_user_choice();
        current_scene = scenes[current_scene].next_scenes[choice];
    }
}

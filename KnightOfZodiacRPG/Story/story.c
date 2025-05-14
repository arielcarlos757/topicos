//
// Created by dev on 9/05/25.
//
#include "story.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../Knight/knights.h"
#include "../Houses/house.h"

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
void print_message(const char *message) {
    printf("\033[1;34m");
    for (int i = 0; message[i]; i++) {
        putchar(message[i]);
        fflush(stdout);
        usleep(50000); // 50ms entre caracteres
    }
    sleep(2);
}
SceneNode* create_ternary_node(int id, const char* dialogue) {
    SceneNode* node = (SceneNode*)malloc(sizeof(SceneNode));
    node->id = id;
    strncpy(node->dialogue, dialogue, MAX_DIALOGUE_LEN);
    for (int i = 0; i < MAX_CHOICES; i++) {
        node->choices[i] = NULL;
        node->is_combat[i] = 0;
        node->required_items[i] = -1;
    }
    return node;
}

SceneNode* load_ternary_story(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    SceneNode* nodes[100] = {NULL}; // Pool de nodos
    char line[MAX_DIALOGUE_LEN * 3]; // Buffer ampliado para líneas largas
    int max_id = 0;

    // Primera pasada: crear todos los nodos
    while (fgets(line, sizeof(line), file)) {
        int id, house_id;
        char dialogue[MAX_DIALOGUE_LEN];

        if (sscanf(line, "%d|%d|%[^|]", &id, &house_id, dialogue) == 3) {
            nodes[id] = create_ternary_node(id, dialogue);
            nodes[id]->house_id = house_id; // Asignar house_id
            max_id = (id > max_id) ? id : max_id;
        }
    }

    // Segunda pasada: conectar nodos y asignar combates/ítems
    rewind(file);
    while (fgets(line, sizeof(line), file) ){
        int id, house_id, ids[MAX_CHOICES], combat[MAX_CHOICES], items[MAX_CHOICES];
        char dialogue[MAX_DIALOGUE_LEN];

        // Parsear TODOS los campos necesarios
        if (sscanf(line, "%d|%d|%[^|]|%d|%d|%d|%d|%d|%d|%d|%d|%d",
                  &id, &house_id, dialogue,
                  &ids[0], &combat[0], &items[0],
                  &ids[1], &combat[1], &items[1],
                  &ids[2], &combat[2], &items[2]) >= 3) { // Mínimo id, house_id y diálogo

            if (nodes[id]) { // Verificar que el nodo existe
                for (int i = 0; i < MAX_CHOICES; i++) {
                    if (ids[i] != -1 && ids[i] <= max_id) {
                        nodes[id]->choices[i] = nodes[ids[i]];
                        nodes[id]->is_combat[i] = combat[i];
                        nodes[id]->required_items[i] = items[i];
                    }
                }
            }
        }
    }

    fclose(file);
    return nodes[0]; // Retorna la raíz (ID 0)
}

void play_ternary_scene(SceneNode* current, House* houses, Knight* players, Knight* golden_knights) {
    if (!current) return;

    printf("\n\033[1;35m[Escena %d]\033[0m\n%s\n", current->id, current->dialogue);

    House* current_house = &houses[current->house_id];

   SceneNode game_over =  (SceneNode){
        .id = 3,
        .dialogue = "¡Has sido derrotado! Game Over.",
        .choices = { NULL, NULL, NULL }, // Fin del juego
        .is_combat = {0, 0, 0},
        .required_items = {-1, -1, -1},
        .house_id = -1
    };
    // Mostrar opciones válidas
    int valid_choices = 0, result;
    int choice_map[MAX_CHOICES] = {-1};

    for (int i = 0; i < MAX_CHOICES; i++) {
        if (current->choices[i]) {
           // if (current->required_items[i] == -1 || has_item(player, current->required_items[i])) {
            if (current->required_items[i] == -1 || true) {
                printf("\033[1;36m%d. %s\033[0m\n", valid_choices + 1, current->choices[i]->dialogue);
                choice_map[valid_choices] = i;
                valid_choices++;
            }
        }
    }

    if (valid_choices == 0) {
        printf("\033[1;31m¡No hay opciones disponibles!\033[0m\n");
        return;
    }

    // Capturar elección
    int choice;
    do {
        printf("> ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > valid_choices);

    int real_choice = choice_map[choice - 1];
    SceneNode* next = players[0].is_alive? current->choices[real_choice]: current->choices[choice];

    if (current->is_combat[real_choice] && players[0].is_alive) {
        result = start_combat(&golden_knights[current->house_id], &players[0]);
        if (result == -1) {
            players[0].is_alive = 0;
        }
    }

    play_ternary_scene(next, houses, players, golden_knights);
}

int start_combat(Knight* enemy,Knight* player) {
    printf("\n=== COMBATE: %s vs %s ===\n", player->name, enemy->name);
    int result;
    while (1) {
        // Turno del jugador
        printf("\n%s: HP %d | Cosmos %d\n", player->name, player->hp, player->cosmos);
        printf("Elige ataque:\n");
        for (int i = 0; i < MAX_ATTACKS; i++) {
            printf("%d. %s\n", i+1, player->special_attacks[i]);
        }

        int choice;
        scanf("%d", &choice);
        int damage = execute_attack(player, choice-1, enemy);
        printf("¡%s inflige %d de daño!\n", player->name, damage);

        // Verificar si el enemigo fue derrotado
        if (determine_winner(player, enemy) == 1) {
            player->cosmos += 30; // Recompensa por victoria
            break;
        }

        // Turno del enemigo (IA simple)
        int enemy_attack = rand() % MAX_ATTACKS;
        damage = execute_attack(enemy, enemy_attack, player);
        printf("¡%s usa %s y causa %d de daño!\n",
               enemy->name,
               enemy->special_attacks[enemy_attack],
               damage);

        // Verificar si el jugador fue derrotado
        result = determine_winner(player, enemy);
        if (result == -1) {
            player->is_alive = 0;
            break;
        }
    }
    return result;
}

void free_ternary_tree(SceneNode* root) {
    if (!root) return;
    for (int i = 0; i < MAX_CHOICES; i++) {
        free_ternary_tree(root->choices[i]);
    }
    free(root);
}

void print_tree(SceneNode* node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) printf("  ");
    printf("└─ [%d] %s\n", node->id, node->dialogue);

    for (int i = 0; i < MAX_CHOICES; i++) {
        print_tree(node->choices[i], depth + 1);
    }
}
// Uso: print_tree(root, 0);
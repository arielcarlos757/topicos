//
// Created by dev on 9/05/25.
//

#ifndef STORY_H
#define STORY_H

#define MAX_TEXT_LENGTH 1024
#define MAX_SCENES 50
#define MAX_DIALOGUE_LEN 1024
#define MAX_CHOICES 3
#include "../Knight/knights.h"
#include "../Houses/house.h"
// Estructura para manejar escenas narrativas
typedef struct {
    int scene_id;
    char dialogue[MAX_TEXT_LENGTH];
    char choices[3][MAX_TEXT_LENGTH];
    int next_scenes[3]; // IDs de las siguientes escenas según elección
} Scene;


typedef struct SceneNode {
    int id;
    char dialogue[MAX_DIALOGUE_LEN];
    struct SceneNode* choices[MAX_CHOICES]; // Array de 3 punteros
    int is_combat[MAX_CHOICES];             // ¿Cada elección lleva a combate?
    int required_items[MAX_CHOICES];
    int house_id;// Ítems necesarios por elección
} SceneNode;

// Prototipos de funciones
void load_story(const char* filename, Scene scenes[], int* total_scenes);
void display_scene(const Scene* scene);
int get_user_choice();
void play_story_arc(const char* arc_file);

// Prototipos
SceneNode* load_ternary_story(const char* filename);
// story.h
void play_ternary_scene(
    SceneNode* scene,
    House* houses,          // Array de casas
    Knight* players,       // Array de caballeros jugadores
    Knight* golden_knights // Array de caballeros dorados
);
void free_ternary_tree(SceneNode* root);
int start_combat(Knight* golden,Knight* player );
void print_tree(SceneNode* node, int depth);
#endif //STORY_H

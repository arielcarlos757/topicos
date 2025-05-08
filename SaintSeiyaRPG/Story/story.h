#ifndef STORY_H_INCLUDED
#define STORY_H_INCLUDED

#define MAX_TEXT_LENGTH 1024
#define MAX_SCENES 50

// Estructura para manejar escenas narrativas
typedef struct {
    int scene_id;
    char dialogue[MAX_TEXT_LENGTH];
    char choices[3][MAX_TEXT_LENGTH];
    int next_scenes[3]; // IDs de las siguientes escenas según elección
} Scene;

// Prototipos de funciones
void load_story(const char* filename, Scene scenes[], int* total_scenes);
void display_scene(const Scene* scene);
int get_user_choice();
void play_story_arc(const char* arc_file);

#endif // STORY_H_INCLUDED

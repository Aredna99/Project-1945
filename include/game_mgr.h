#ifndef GAME_MGR_H
#define GAME_MGR_H
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <time.h>
#include "scene.h"
#include "audio_mgr.h"

typedef struct {
    game_scene* game_scene;
    title_scene* title_scene;
    boolean* quit;
    boolean* is_game_active;
} game_mgr;

game_mgr* init_game();
void update_title_scene(game_mgr* game);
void update_1945_game();
void destroy_game(game_mgr* game);

#endif
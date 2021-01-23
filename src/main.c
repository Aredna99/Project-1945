#define SDL_MAIN_HANDLED
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <time.h>
#include "scene.h"
#include "audio_mgr.h"
#include "game_mgr.h"

typedef struct {
    float x;
    float y;
} vec2;

int main() {
    game_mgr* game = init_game();
    update_title_scene(game);

    return 0;
}
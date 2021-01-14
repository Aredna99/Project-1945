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
    /*SDL_Init(SDL_INIT_VIDEO);
    srand(time(NULL));
    create_window();
    create_renderer();

    init_utils();
    init_font_mgr();
    init_audiomgr(&audiomgr);
    
    game_scene* my_scene = create_game_scene();

    boolean* done = false;   
    while (!done) {
        update_utils(done);

        // Clear
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        
        draw_scene(my_scene);

        SDL_Delay(11);

        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);  
    SDL_Quit();*/
    game_mgr* game = init_game();
    update_title_scene(game);
    //update_1945_game(game);

    return 0;
}
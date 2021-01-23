#include "game_mgr.h"

game_mgr* init_game() {
    SDL_Init(SDL_INIT_VIDEO);
    srand(time(NULL));
    create_window();
    create_renderer();

    init_utils();
    init_font_mgr();
    init_audiomgr(&audiomgr);
    
    game_mgr* game = (game_mgr*)malloc(sizeof(game_mgr));
    game->game_scene = (game_scene*)malloc(sizeof(game_scene));
    game->title_scene = (title_scene*)malloc(sizeof(title_scene));
    game->game_scene = create_game_scene();
    game->title_scene = create_title_scene();
    game->quit = false;
    game->is_game_active = false;

    return game;
}

void update_title_scene(game_mgr* game) {
    while (!game->quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game->quit = true;
                break;
            }
            else if(event.key.keysym.sym == SDLK_ESCAPE) {
                game->quit = true;
                break;
            }
        }
         
        update_utils(game->quit);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        if(!game->is_game_active) {
            draw_title_scene(game->title_scene, game->is_game_active, game->quit);

            if(SDL_HasIntersection(game->title_scene->rect_mouse_pos, game->title_scene->rect_start_game)) {
                if(event.type == SDL_MOUSEBUTTONDOWN) {
                    game->is_game_active = true;
                    Mix_PlayMusic(audiomgr.bg_music, -1);
                }
            }
            else if(SDL_HasIntersection(game->title_scene->rect_mouse_pos, game->title_scene->rect_quit_game)) {
                if(event.type == SDL_MOUSEBUTTONDOWN) {
                    game->quit = true;
                }
            }
        }
        else {
            draw_game_scene(game->game_scene);
        }
        SDL_Delay(11);
        SDL_RenderPresent(renderer);
    }

    destroy_game(game);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);  
    SDL_Quit();
}

void update_1945_game(game_mgr* game) {
    while (!game->quit) {
        update_utils(game->quit);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        
        draw_game_scene(game->game_scene);

        SDL_Delay(11);

        SDL_RenderPresent(renderer);
    }
    destroy_game(game);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);  
    SDL_Quit();
}

void destroy_game(game_mgr* game) {
    destroy_game_scene(game->game_scene);
    destroy_title_scene(game->title_scene);
    free(game);
}
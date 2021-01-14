#include "font_mgr.h"

void init_font_mgr() {

    if(!TTF_WasInit() && TTF_Init() == -1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init: %s\n", TTF_GetError());
        return;
    }

    fontmgr.font = TTF_OpenFont("resources/assets/font/atari.ttf", 18);
    
    fontmgr.color_font.r = 255;
    fontmgr.color_font.g = 240;
    fontmgr.color_font.b = 240;
    fontmgr.color_font.a = 255;
}

void change_score_text(SDL_Rect* rect_hp, float hp_bar_offset_x, int score) {
    fontmgr.score_size = floor(log10(abs(score))) + 1;

    if(fontmgr.score_size <= 0) 
        fontmgr.score_size = 1;

    char player_score_to_string[100];
    sprintf(player_score_to_string, "%d", score); // this should set my score to player_score_to_string

    SDL_Surface* score_surface = TTF_RenderText_Solid(fontmgr.font, player_score_to_string, fontmgr.color_font);
    if(fontmgr.score_texture != NULL){
        SDL_DestroyTexture(fontmgr.score_texture);
    }
    fontmgr.score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);

    fontmgr.score_rect.x = rect_hp->x + hp_bar_offset_x + 42;
    fontmgr.score_rect.y = rect_hp->y - 8;
    fontmgr.score_rect.w = 12 * fontmgr.score_size;
    fontmgr.score_rect.h = 18;

    SDL_FreeSurface(score_surface);
}

void draw_score() {
    SDL_RenderCopy(renderer, fontmgr.score_texture, NULL, &fontmgr.score_rect);
}

void draw_titles() {
    SDL_RenderCopy(renderer, fontmgr.start_game_texture, NULL, &fontmgr.start_game_rect);
    SDL_RenderCopy(renderer, fontmgr.quit_game_texture, NULL, &fontmgr.quit_game_rect);
}

void write_title_scene(SDL_Rect* start_game_rect, SDL_Rect* quit_game_rect) {
    SDL_Surface* start_surf = TTF_RenderText_Solid(fontmgr.font, "Start a game!", fontmgr.color_font); 
    SDL_Surface* quit_surf = TTF_RenderText_Solid(fontmgr.font, "Quit the game!", fontmgr.color_font); 


    fontmgr.start_game_texture = SDL_CreateTextureFromSurface(renderer, start_surf);
    fontmgr.quit_game_texture = SDL_CreateTextureFromSurface(renderer, quit_surf);
    
    fontmgr.start_game_rect.w = 168;
    fontmgr.start_game_rect.h = 30;
    fontmgr.start_game_rect.x = WINDOW_WIDTH / 2;
    fontmgr.start_game_rect.y = WINDOW_HEIGHT / 2;

    start_game_rect->w = fontmgr.start_game_rect.w;
    start_game_rect->h = fontmgr.start_game_rect.h;
    start_game_rect->x = fontmgr.start_game_rect.x;
    start_game_rect->y = fontmgr.start_game_rect.y;

    fontmgr.quit_game_rect.w = 180;
    fontmgr.quit_game_rect.h = 30;
    fontmgr.quit_game_rect.x = WINDOW_WIDTH / 2;
    fontmgr.quit_game_rect.y = WINDOW_HEIGHT / 2 + 100;

    quit_game_rect->w = fontmgr.quit_game_rect.w;
    quit_game_rect->h = fontmgr.quit_game_rect.h;
    quit_game_rect->x = fontmgr.quit_game_rect.x;
    quit_game_rect->y = fontmgr.quit_game_rect.y;

    SDL_FreeSurface(start_surf);
    SDL_FreeSurface(quit_surf);

}
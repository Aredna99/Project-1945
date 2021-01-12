#include "font_mgr.h"

void Init_FontMgr() {

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

    //SDL_Surface* surf = TTF_RenderText_Solid(fontmgr.font, "Hello!!!", fontmgr.color_font); 
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

void Draw_Score() {
    SDL_RenderCopy(renderer, fontmgr.score_texture, NULL, &fontmgr.score_rect);
}
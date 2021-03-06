#ifndef FONT_MGR_H
#define FONT_MGR_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <utils.h>
#include <stdio.h>

typedef struct {
    TTF_Font* font;                     //type of font used for the text
    SDL_Texture* score_texture;         //texture that will be draw from the score of the player
    SDL_Texture* start_game_texture;    //texture that will be draw from the score of the player
    SDL_Texture* quit_game_texture;     //texture that will be draw from the score of the player
    SDL_Color color_font;               //color of the font
    SDL_Rect score_rect;                //variable size of the rect that contains the player's score
    SDL_Rect start_game_rect;           //variable size of the rect that contains the player's score
    SDL_Rect quit_game_rect;            //variable size of the rect that contains the player's score
    int score_size;                     //sign the number of characters that there are in the score. ES: [•1 ---> 1] [•10 ---> 2] [•100 ---> 3]
} font_mgr;

font_mgr fontmgr;

void init_font_mgr();
void change_score_text(SDL_Rect* rect_hp, float hp_bar_offset_x, int score);
void write_title_scene(SDL_Rect* start_game_rect, SDL_Rect* quit_game_rect);
void draw_score();
void draw_titles();

#endif
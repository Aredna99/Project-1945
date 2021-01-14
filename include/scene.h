#ifndef SCENE_H
#define SCENE_H
#include <player.h>
#include <enemy.h>
#include <island.h>

typedef struct {
    SDL_Texture* water_texture;
    SDL_Texture* bg_ui_bottom_texture;
    SDL_Texture* ui_player_life_texture;

    SDL_Rect** bg_rect;                         //Array of water_rect in the background
    SDL_Rect* bottom_ui_rect;                   //Rect of the panel in the bottom of the screen
    SDL_Rect* ui_player_life_rect;              //Rect of the texture of the player's life
    SDL_Rect* hp_bar_rect;                      //Rect of the texture of the player's bar life

    player* player;
    enemy** enemies;                            //Array of enemies
    island** islands;                           //Array of islands

    int bg_water_rect_capacity;
    int enemy_count;                            //Max number of enemy in the same instant in the same frame
    int island_count;                           //Max number of islands in the same instant in the same frame

    float max_hp_bar_width;                     //Size of player's hp bar
    float default_cd_enemy_spawn;               //Variable time with which enemies are spawned between min and max rnd count down
    float min_rnd_cd_enemy_spawn;               //Min time of count down for spawn enemies
    float max_rnd_cd_enemy_spawn;               //Max time of count down for spawn enemies
    float cd_enemy_spawn;                       //Variable that increase with delta_time till reach the default_cd_enemy_spawn variable
    float default_cd_island_spawn;              //Variable time with which islands are spawned between min and max rnd count down
    float min_rnd_cd_island_spawn;              //Min time of count down for spawn islands
    float max_rnd_cd_island_spawn;              //Max time of count down for spawn islands
    float cd_island_spawn;                      //Variable that increase with delta_time till reach the default_cd_island_spawn variable
    float default_cd_restart_game;              //Time with which the game restart
    float cd_restart_game;                      //Time before the game restart
} game_scene;

typedef struct {
    SDL_Texture* texture_bg;                    //Background texture full window
    SDL_Texture* texture_stuff;                 //idk maybe the texture for something in the scene

    SDL_Rect* rect_start_game;                  //Rect of the start game panel in the upper center  of the screen
    SDL_Rect* rect_quit_game;                   //Rect of the quit game panel in the upper center  of the screen
    SDL_Rect* rect_mouse_pos;                   //Rect of the current position of the mouse inside the window

} title_scene;

game_scene* create_game_scene();
title_scene* create_title_scene();
void reset_game_scene(game_scene* scene);
void create_bg(game_scene* scene);
void spawn_enemy(game_scene* scene);
void spawn_island(game_scene* scene);
void draw_ui(game_scene* scene);
void update_player_life(game_scene* scene);
void check_enemy_bullet_collision(game_scene* scene);
void check_enemy_collision(game_scene* scene);
void check_collisions(game_scene* scene);
void player_add_score(game_scene* scene, int points);
void draw_game_scene(game_scene* scene);
void draw_title_scene(title_scene* scene, boolean* play, boolean* quit);

#endif
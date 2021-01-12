#ifndef SCENE_H
#define SCENE_H
#include <player.h>
#include <enemy.h>
#include <island.h>

typedef struct {
    SDL_Texture* water_texture;
    SDL_Texture* bg_ui_bottom_texture;
    SDL_Texture* ui_player_life_texture;

    SDL_Rect** bg_rect;                         //array of water_rect in the background
    SDL_Rect* bottom_ui_rect;                   //rect of the panel in the bottom of the screen
    SDL_Rect* ui_player_life_rect;              //rect of the texture of the player's life
    SDL_Rect* hp_bar_rect;                      //rect of the texture of the player's bar life

    player* player;
    enemy** enemies;                            //array of enemies
    island** islands;                           //array of islands

    int bg_water_rect_capacity;
    int enemy_count;                            //max number of enemy in the same instant in the same frame
    int island_count;                           //max number of islands in the same instant in the same frame

    float max_hp_bar_width;                     //size of player's hp bar
    float default_cd_enemy_spawn;               //variable time with which enemies are spawned between min and max rnd count down
    float min_rnd_cd_enemy_spawn;               //min time of count down for spawn enemies
    float max_rnd_cd_enemy_spawn;               //max time of count down for spawn enemies
    float cd_enemy_spawn;                       //variable that increase with delta_time till reach the default_cd_enemy_spawn variable
    float default_cd_island_spawn;              //variable time with which islands are spawned between min and max rnd count down
    float min_rnd_cd_island_spawn;              //min time of count down for spawn islands
    float max_rnd_cd_island_spawn;              //max time of count down for spawn islands
    float cd_island_spawn;                      //variable that increase with delta_time till reach the default_cd_island_spawn variable
} scene;

scene* create_scene();
void draw_scene(scene* scene);
void create_bg(scene* scene);
void spawn_enemy(scene* scene);
void spawn_island(scene* scene);
void draw_ui(scene* scene);
void update_player_life(scene* my_scene);
void check_enemy_bullet_collision(scene* scene);
void check_enemy_collision(scene* scene);
void check_collisions(scene* scene);
void player_add_score(scene* scene, int points);

#endif
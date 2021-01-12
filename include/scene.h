#ifndef SCENE_H
#define SCENE_H
#include <SDL.h>
#include <SDL_image.h>
#include <player.h>
#include <enemy.h>
#include <island.h>

typedef struct {
    SDL_Texture* water_texture;
    SDL_Texture* bg_ui_bottom_texture;
    SDL_Texture* ui_player_life_texture;

    SDL_Rect** bg_rect;
    SDL_Rect* bottom_ui_rect;
    SDL_Rect* ui_player_life_rect;
    SDL_Rect* hp_bar_rect;

    enemy** enemies;
    island** islands;

    int bg_water_rect_capacity;
    int enemy_count;
    int island_count;

    float max_hp_bar_width;
    float default_cd_enemy_spawn;
    float min_rnd_cd_enemy_spawn;
    float max_rnd_cd_enemy_spawn;
    float cd_enemy_spawn;
    float default_cd_island_spawn;
    float min_rnd_cd_island_spawn;
    float max_rnd_cd_island_spawn;
    float cd_island_spawn;
} scene;

scene* create_scene();
void draw_scene(scene* scene, player* player);
void create_bg(scene* scene);
void spawn_enemy(scene* scene);
void spawn_island(scene* scene);
void draw_ui(scene* scene, player* player);
void update_player_life(scene* my_scene, player* my_player);
void check_enemy_bullet_collision(scene* scene, player* player);
void check_enemy_collision(scene* scene, player* player);
void check_collisions(scene* scene, player* player);
void player_add_score(player* player, int points);

#endif
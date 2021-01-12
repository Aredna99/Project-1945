#ifndef BULLET_H
#define BULLET_H
#include <render_mgr.h>
#include <utils.h>

typedef struct {
    SDL_Texture* texture;
    SDL_Rect* rect;
    boolean is_active;

    float speed;
    int damage;
} bullet;

typedef struct {
    bullet* bullet;
} player_bullet;

typedef struct {
    bullet* bullet;
} enemy_bullet;

player_bullet* create_player_bullet();
enemy_bullet* create_enemy_bullet();
void check_collision();
void update_bullets_pos(bullet* bullet);
void check_bullet_bounds(SDL_Rect* rect);

#endif
#ifndef PLAYER_H
#define PLAYER_H
#include "actor.h"
#include "input.h"
#include "bullet.h"

typedef struct {
    actor* actor;
    player_bullet** bullets;

    boolean is_alive;
    boolean is_invulnerable;
    boolean blink;

    int bullets_count;
    int lifes;
    int score;
    float default_shoot_cd;
    float shoot_cd;
    float default_invulnerability_cd;
    float invulnerability_cd;
} player;

player* create_player();
void player_input();
void check_player_bounds(SDL_Rect* pos_rect);
void update_player(player* player); 
void update_player_bullets(player* player);
void player_take_damage(player* player, float damage);
void draw_player(player* player);
#endif

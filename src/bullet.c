#include <bullet.h>

player_bullet* create_player_bullet() {
    player_bullet* new_bullet = (player_bullet*)malloc(sizeof(player_bullet));
    new_bullet->bullet = (bullet*)malloc(sizeof(bullet));
    
    new_bullet->bullet->texture = create_texture("resources/assets/player/bullet.png");


    new_bullet->bullet->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    new_bullet->bullet->rect->h = 32;
    new_bullet->bullet->rect->w = 32;
    new_bullet->bullet->rect->x = 0;
    new_bullet->bullet->rect->y = 0;

    new_bullet->bullet->speed = 0;
    new_bullet->bullet->damage = 10;
    new_bullet->bullet->is_active = false;

    return new_bullet;
}

enemy_bullet* create_enemy_bullet() {
    enemy_bullet* new_bullet = (enemy_bullet*)malloc(sizeof(enemy_bullet));
    new_bullet->bullet = (bullet*)malloc(sizeof(bullet));

    new_bullet->bullet->texture = create_texture("resources/assets/enemy/enemybullet1.png");

    new_bullet->bullet->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    new_bullet->bullet->rect->h = 32;
    new_bullet->bullet->rect->w = 32;
    new_bullet->bullet->rect->x = 0;
    new_bullet->bullet->rect->y = 0;

    new_bullet->bullet->speed = 0;
    new_bullet->bullet->damage = 20;

    new_bullet->bullet->is_active = false;

    return new_bullet;
}

void update_bullets_pos(bullet* bullet) {
    bullet->rect->y += (int)(bullet->speed * delta_time);

    check_bullet_bounds(bullet);

    if(bullet->is_active) {
        SDL_RenderCopy(renderer, bullet->texture, NULL, bullet->rect);
    }
}

void check_bullet_bounds(bullet* bullet) {
    if(bullet->rect->x < - bullet->rect->w) {
        bullet->is_active = false;
    }
    else if(bullet->rect->x > WINDOW_WIDTH + bullet->rect->w) {
        bullet->is_active = false;
    }

    if(bullet->rect->y < -bullet->rect->h) {
        bullet->is_active = false;
    }
    else if(bullet->rect->y > (WINDOW_HEIGHT - BOTTOM_UI_ELEMENT_HIGHT_SCREEN) + bullet->rect->h) {
        bullet->is_active = false;
    }
}

void check_collision() {

}
#include <enemy.h>
#include <stdio.h>

enemy* create_enemy() {
    enemy* en = (enemy*)malloc(sizeof(enemy));
    en->actor = (actor*)malloc(sizeof(actor));
    en->actor->texture = create_texture("resources/assets/enemy/enemy1_strip3.png");
    en->actor->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    en->actor->anim_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

    en->actor->rect->w = 32;
    en->actor->rect->h = 32;
    set_enemy_spawnpoint(en->actor->rect);

    en->actor->anim_rect->w = 32;
    en->actor->anim_rect->h = 32;
    en->actor->anim_rect->x = 0;
    en->actor->anim_rect->y = 0;

    en->actor->curr_anim_frame = 0;
    en->actor->anim_frames = 3;
    en->actor->max_anim_time = 0.1f;
    en->actor->curr_anim_time = 0;

    en->actor->collider_radius = 5.f;
    en->actor->speed = 100;
    en->actor->max_health = 10;
    en->actor->health = en->actor->max_health;
    en->is_active = false;
    en->bullets_count = 3;
    en->bullets = (enemy_bullet**)malloc(en->bullets_count * sizeof(enemy_bullet*));

    for (int i = 0; i < en->bullets_count; i++)
    {
        en->bullets[i] = (enemy_bullet*)malloc(sizeof(enemy_bullet));
        en->bullets[i] = create_enemy_bullet();
    }
    
    en->default_shoot_cd = rand() % 5 + 2;
    en->shoot_cd = 0.f;

    return en;
}

void set_enemy_spawnpoint(SDL_Rect* rect) {
    rect->x = rand() % (WINDOW_WIDTH - rect->w);
    rect->y = -rect->h;
}

void instantiate_enemy(enemy* en) {
    set_enemy_spawnpoint(en->actor->rect);
    en->is_active = true;
}

void check_enemy_bounds(enemy* en) {
    if(en->actor->rect->y > WINDOW_HEIGHT - BOTTOM_UI_ELEMENT_HIGHT_SCREEN) {
        en->is_active = false;
    }
}

void update_enemy_movement(enemy* en) {
    en->actor->rect->y += (int)(en->actor->speed * delta_time);
}

void enemy_shoot(enemy* en, bullet* enemy_bullet) {
    enemy_bullet->is_active = true;

    enemy_bullet->rect->x = en->actor->rect->x + (en->actor->rect->w / 2) - (enemy_bullet->rect->w / 2);
    enemy_bullet->rect->y = en->actor->rect->y +  enemy_bullet->rect->h;

    enemy_bullet->speed = en->actor->speed + 100.f;
}

void update_enemy_bullets(enemy* en) {
    for (int i = 0; i < en->bullets_count; i++)
    {   
        if(en->bullets[i]->bullet->is_active) {
            update_bullets_pos(en->bullets[i]->bullet);
        }
    }
}

void enemy_ready_to_shoot(enemy* en) {
    for (int i = 0; i < en->bullets_count; i++)
    {
        if(!en->bullets[i]->bullet->is_active) {
            if(en->shoot_cd >= en->default_shoot_cd){
                en->shoot_cd -= en->default_shoot_cd;
                en->default_shoot_cd = rand() % 20 + 2;
                enemy_shoot(en, en->bullets[i]->bullet);
                break;
            }
        }
    }
    en->shoot_cd += delta_time;
}

void update_enemy(enemy* en) {
    if(en->is_active) {
        update_enemy_movement(en);
        enemy_ready_to_shoot(en);
        update_enemy_bullets(en);
        animate_rect(en->actor->anim_rect, &en->actor->anim_frames, &en->actor->curr_anim_frame, &en->actor->max_anim_time, &en->actor->curr_anim_time);
        SDL_RenderCopy(renderer, en->actor->texture, en->actor->anim_rect, en->actor->rect);
        check_enemy_bounds(en);
    }
}

void enemy_take_damage(enemy* enemy, float damage) {
    enemy->actor->health -= damage;
    if(enemy->actor->health <= 0) {
        enemy->is_active = false;
        enemy->actor->health = enemy->actor->max_health;
    }
}

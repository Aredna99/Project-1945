#include <scene.h>
#include <stdio.h>

scene* create_scene() {
    scene* new_scene = (scene*)malloc(sizeof(scene));
    create_bg(new_scene);

    new_scene->water_texture = create_texture("resources/assets/map/water.png");
    new_scene->bg_ui_bottom_texture = create_texture("resources/assets/ui/bottom.png");
    new_scene->ui_player_life_texture = create_texture("resources/assets/ui/life.png");

    new_scene->enemy_count = 10;
    new_scene->island_count = 10;
    
    new_scene->enemies = (enemy**)malloc(new_scene->enemy_count * sizeof(enemy*));
    new_scene->islands = (island**)malloc(new_scene->island_count * sizeof(island*));
    new_scene->bottom_ui_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    new_scene->ui_player_life_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect*));
    new_scene->hp_bar_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect*));

    new_scene->bottom_ui_rect->w = 640;
    new_scene->bottom_ui_rect->h = 76;
    new_scene->bottom_ui_rect->x = 0;
    new_scene->bottom_ui_rect->y = WINDOW_HEIGHT - new_scene->bottom_ui_rect->h;

    new_scene->hp_bar_rect->h = 9;
    new_scene->hp_bar_rect->w = 126;
    new_scene->hp_bar_rect->x = 12;
    new_scene->hp_bar_rect->y = new_scene->bottom_ui_rect->y + 45;
    new_scene->max_hp_bar_width = new_scene->hp_bar_rect->w;

    new_scene->ui_player_life_rect->h = 32;
    new_scene->ui_player_life_rect->w = 32;
    new_scene->ui_player_life_rect->x = 12;
    new_scene->ui_player_life_rect->y = new_scene->hp_bar_rect->y - new_scene->ui_player_life_rect->h;

    for (int i = 0; i < new_scene->enemy_count; i++)
    {
        new_scene->enemies[i] = (enemy*)malloc(sizeof(enemy));
        new_scene->enemies[i] = create_enemy();
    }

    for (int i = 0; i < new_scene->island_count; i++)
    {
        new_scene->islands[i] = (island*)malloc(sizeof(island));
        new_scene->islands[i] = create_island();
    }
    
    new_scene->default_cd_enemy_spawn = 1.f;
    new_scene->min_rnd_cd_enemy_spawn = 0.f;
    new_scene->max_rnd_cd_enemy_spawn = 2.f;
    new_scene->cd_enemy_spawn = new_scene->default_cd_enemy_spawn;

    new_scene->default_cd_island_spawn = 1.f;
    new_scene->min_rnd_cd_island_spawn = 1.f;
    new_scene->max_rnd_cd_island_spawn = 4.f;
    new_scene->cd_island_spawn = 0;
    
    return new_scene;
}

void create_bg(scene* scene) {

    int width = (int)(WINDOW_WIDTH / 32);
    int height = (int)(WINDOW_HEIGHT / 32);

    scene->bg_rect = (SDL_Rect**)malloc(width * height * sizeof(SDL_Rect*));

    scene->bg_water_rect_capacity = width * height;
    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            scene->bg_rect[(y * width) + x] = (SDL_Rect*)malloc(sizeof(SDL_Rect));
            scene->bg_rect[(y * width) + x]->x = x * 32;
            scene->bg_rect[(y * width) + x]->y = y * 32;
            scene->bg_rect[(y * width) + x]->w = 32;
            scene->bg_rect[(y * width) + x]->h = 32;
        }
    }
}

void spawn_enemy(scene* scene) {
    for (int i = 0; i < scene->enemy_count; i++)
    {
        if(!scene->enemies[i]->is_active) {
            if(scene->cd_enemy_spawn >= scene->default_cd_enemy_spawn) {
                scene->cd_enemy_spawn -= scene->default_cd_enemy_spawn;
                // change the cd for spawn the enemy every time that an enemy has been spawned  
                scene->default_cd_enemy_spawn = rand() % (int)scene->max_rnd_cd_enemy_spawn + (int)scene->min_rnd_cd_enemy_spawn;
                instantiate_enemy(scene->enemies[i]);
                break;
            }
        }
    }
    scene->cd_enemy_spawn += delta_time;
}

void spawn_island(scene* scene) {
    for (int i = 0; i < scene->island_count; i++)
    {
        if(!scene->islands[i]->is_active) {
            if(scene->cd_island_spawn >= scene->default_cd_island_spawn) {
                scene->cd_island_spawn -= scene->default_cd_island_spawn;
                // change the cd for spawn the enemy every time that an enemy has been spawned  
                scene->default_cd_island_spawn = rand() % (int)scene->max_rnd_cd_island_spawn + (int)scene->min_rnd_cd_island_spawn;
                instantiate_island(scene->islands[i]);
                break;
            }
        }
    }
    scene->cd_island_spawn += delta_time;
}

void update_player_life(scene* my_scene, player* my_player) {
    my_scene->hp_bar_rect->w = (my_scene->max_hp_bar_width * my_player->actor->health) / my_player->actor->max_health;
}

void draw_ui(scene* my_scene ,player* my_player) {
    SDL_RenderCopy(renderer, my_scene->bg_ui_bottom_texture, NULL, my_scene->bottom_ui_rect);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   
    SDL_RenderFillRect(renderer, my_scene->hp_bar_rect);
    for (int i = 0; i < my_player->lifes; i++)
    {
        my_scene->ui_player_life_rect->x = (my_scene->ui_player_life_rect->w * i) + 12;
        SDL_RenderCopy(renderer, my_scene->ui_player_life_texture, NULL, my_scene->ui_player_life_rect);
    }
}

void check_enemy_bullet_collision(scene* my_scene, player* my_player) {
    for (int i = 0; i < my_scene->enemy_count; i++)
    {
        for (int j = 0; j < my_scene->enemies[i]->bullets_count; j++)
        {
            if(my_scene->enemies[i]->bullets[j]->bullet->is_active) {
                // collision enemy_bullet ---> player
                if(my_scene->enemies[i]->bullets[j]->bullet->is_active && my_player->is_alive && !my_player->is_invulnerable){
                    if(SDL_HasIntersection(my_scene->enemies[i]->bullets[j]->bullet->rect, my_player->actor->rect)) {    
                        my_scene->enemies[i]->bullets[j]->bullet->is_active = false;
                        player_take_damage(my_player, my_scene->enemies[i]->bullets[j]->bullet->damage);
                        return;
                    }
                }
                // collision enemy_bullet ---> player_bullet
                for (int k = 0; k < my_player->bullets_count; k++)
                {
                    if(my_scene->enemies[i]->bullets[j]->bullet->is_active && my_player->bullets[k]->bullet->is_active && SDL_HasIntersection(my_scene->enemies[i]->bullets[j]->bullet->rect, my_player->bullets[k]->bullet->rect)){
                        my_scene->enemies[i]->bullets[j]->bullet->is_active = false;
                        my_player->bullets[k]->bullet->is_active = false;
                        return;
                    }
                }
            }
        }
    }
}

void check_enemy_collision(scene* my_scene, player* my_player) {
    for (int i = 0; i < my_scene->enemy_count; i++)
    {
        if(my_scene->enemies[i]->is_active) {
            if(my_player->is_alive && !my_player->is_invulnerable  && my_scene->enemies[i]->is_active) {
                // collisione enemy ---> player
                if(SDL_HasIntersection(my_scene->enemies[i]->actor->rect, my_player->actor->rect)) {
                    my_scene->enemies[i]->is_active = false;
                    player_take_damage(my_player, 10);
                    player_add_score(my_player, 10);
                    return;
                }
            }

            for (int j = 0; j < my_player->bullets_count; j++)
            {
                // collision enemy ---> player_bullet
                if(my_player->bullets[j]->bullet->is_active && SDL_HasIntersection(my_scene->enemies[i]->actor->rect, my_player->bullets[j]->bullet->rect)) {
                    my_player->bullets[j]->bullet->is_active = false;
                    enemy_take_damage(my_scene->enemies[i], my_player->bullets[j]->bullet->damage);
                    if(!my_scene->enemies[i]->is_active) {
                        player_add_score(my_player, 10);
                    }
                    return;
                }
            }
        }
    }
}

void player_add_score(player* player, int points) {
    player->score += points;
}

void check_collisions(scene* scene, player* player) {
    check_enemy_bullet_collision(scene, player);
    check_enemy_collision(scene, player);
}

void draw_scene(scene* my_scene, player* my_player) {

    // draw the water_bg
    for (int i = 0; i < my_scene->bg_water_rect_capacity; i++)
    {
        SDL_RenderCopy(renderer, my_scene->water_texture, NULL, my_scene->bg_rect[i]);
    }
    // draw and update the islands
    for (int i = 0; i < my_scene->island_count; i++)
    {
        update_island(my_scene->islands[i]);
    }
    // draw enemies and their bullets
    for (int i = 0; i < my_scene->enemy_count; i++)
    {
        update_enemy(my_scene->enemies[i]);
    }
    // drawn and update the player and his bullets
    update_player(my_player);
    // check all collisions
    check_collisions(my_scene, my_player);
    // change player status like hp, lifes etc...
    update_player_life(my_scene, my_player);
    draw_ui(my_scene, my_player);
    spawn_enemy(my_scene);
    spawn_island(my_scene);
}
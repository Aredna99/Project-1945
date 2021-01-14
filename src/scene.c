#include <scene.h>
#include <stdio.h>

game_scene* create_game_scene() {
    game_scene* new_scene = (game_scene*)malloc(sizeof(game_scene));
    create_bg(new_scene);

    new_scene->water_texture = create_texture("resources/assets/map/water.png");
    new_scene->bg_ui_bottom_texture = create_texture("resources/assets/ui/bottom.png");
    new_scene->ui_player_life_texture = create_texture("resources/assets/ui/life.png");

    new_scene->enemy_count = 10;
    new_scene->island_count = 10;
    
    new_scene->player = (player*)malloc(sizeof(player));
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

    new_scene->player = create_player();
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
    new_scene->default_cd_restart_game = 2.f;
    new_scene->cd_restart_game = 0.f;
    
    return new_scene;
}

title_scene* create_title_scene() {
    title_scene* ttl_scene = (title_scene*)malloc(sizeof(title_scene));
    ttl_scene->rect_start_game = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    ttl_scene->rect_quit_game = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    ttl_scene->rect_mouse_pos = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    ttl_scene->texture_bg = create_texture("resources/assets/extra/Title.png");

    ttl_scene->rect_mouse_pos->h = 20;
    ttl_scene->rect_mouse_pos->w = 20;

    write_title_scene(ttl_scene->rect_start_game, ttl_scene->rect_quit_game);

    return ttl_scene;
}

void create_bg(game_scene* scene) {

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

void spawn_enemy(game_scene* scene) {
    for (int i = 0; i < scene->enemy_count; i++)
    {
        if(!scene->enemies[i]->is_active && !scene->enemies[i]->is_dead) {
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

void spawn_island(game_scene* scene) {
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

void update_player_life(game_scene* my_scene) {
    my_scene->hp_bar_rect->w = (my_scene->max_hp_bar_width * my_scene->player->actor->health) / my_scene->player->actor->max_health;
}

void draw_ui(game_scene* my_scene) {
    SDL_RenderCopy(renderer, my_scene->bg_ui_bottom_texture, NULL, my_scene->bottom_ui_rect);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   
    SDL_RenderFillRect(renderer, my_scene->hp_bar_rect);
    for (int i = 0; i < my_scene->player->lifes; i++)
    {
        my_scene->ui_player_life_rect->x = (my_scene->ui_player_life_rect->w * i) + 12;
        SDL_RenderCopy(renderer, my_scene->ui_player_life_texture, NULL, my_scene->ui_player_life_rect);
    }
    draw_score();
}

void check_enemy_bullet_collision(game_scene* my_scene) {
    for (int i = 0; i < my_scene->enemy_count; i++)
    {
        for (int j = 0; j < my_scene->enemies[i]->bullets_count; j++)
        {
            if(my_scene->enemies[i]->bullets[j]->bullet->is_active) {
                // collision enemy_bullet ---> player
                if(my_scene->enemies[i]->bullets[j]->bullet->is_active && my_scene->player->is_alive && !my_scene->player->is_invulnerable){
                    if(SDL_HasIntersection(my_scene->enemies[i]->bullets[j]->bullet->rect, my_scene->player->actor->rect)) {    
                        my_scene->enemies[i]->bullets[j]->bullet->is_active = false;
                        player_take_damage(my_scene->player, my_scene->enemies[i]->bullets[j]->bullet->damage);
                        return;
                    }
                }
                // collision enemy_bullet ---> player_bullet
                for (int k = 0; k < my_scene->player->bullets_count; k++)
                {
                    if(my_scene->enemies[i]->bullets[j]->bullet->is_active && my_scene->player->bullets[k]->bullet->is_active && SDL_HasIntersection(my_scene->enemies[i]->bullets[j]->bullet->rect, my_scene->player->bullets[k]->bullet->rect)){
                        my_scene->enemies[i]->bullets[j]->bullet->is_active = false;
                        my_scene->player->bullets[k]->bullet->is_active = false;
                        player_add_score(my_scene, 10);
                        return;
                    }
                }
            }
        }
    }
}

void check_enemy_collision(game_scene* my_scene) {
    for (int i = 0; i < my_scene->enemy_count; i++)
    {
        if(my_scene->enemies[i]->is_active) {
            if(my_scene->player->is_alive && !my_scene->player->is_invulnerable && my_scene->enemies[i]->is_active) {
                // collisione enemy ---> player
                if(SDL_HasIntersection(my_scene->enemies[i]->actor->rect, my_scene->player->actor->rect)) {
                    enemy_take_damage(my_scene->enemies[i], my_scene->player->bullets[0]->bullet->damage);
                    player_take_damage(my_scene->player, my_scene->enemies[i]->body_damage);
                    player_add_score(my_scene, my_scene->enemies[i]->score);
                    return;
                }
            }

            for (int j = 0; j < my_scene->player->bullets_count; j++)
            {
                // collision enemy ---> player_bullet
                if(my_scene->player->bullets[j]->bullet->is_active && SDL_HasIntersection(my_scene->enemies[i]->actor->rect, my_scene->player->bullets[j]->bullet->rect)) {
                    my_scene->player->bullets[j]->bullet->is_active = false;
                    enemy_take_damage(my_scene->enemies[i], my_scene->player->bullets[j]->bullet->damage);
                    if(!my_scene->enemies[i]->is_active) {
                        player_add_score(my_scene, my_scene->enemies[i]->score);
                    }
                    return;
                }
            }
        }
    }
}

void player_add_score(game_scene* scene, int points) {
    scene->player->score += points;
    change_score_text(scene->hp_bar_rect, scene->max_hp_bar_width, scene->player->score);
}

void check_collisions(game_scene* scene) {
    check_enemy_bullet_collision(scene, scene->player);
    check_enemy_collision(scene, scene->player);
}

void draw_game_scene(game_scene* my_scene) {
    if(my_scene->cd_restart_game >= my_scene->default_cd_restart_game) {
        if(my_scene->cd_restart_game >= my_scene->default_cd_restart_game) {
            my_scene->cd_restart_game -= my_scene->default_cd_restart_game;
            reset_game_scene(my_scene);
        }
    }
    else {
        if(!my_scene->player->is_alive && !my_scene->player->is_dead)
            my_scene->cd_restart_game += delta_time;

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
        update_player(my_scene->player);
        // check all collisions
        check_collisions(my_scene, my_scene->player);
        // change player status like hp, lifes etc...
        update_player_life(my_scene, my_scene->player);
        draw_ui(my_scene, my_scene->player);
        spawn_enemy(my_scene);
        spawn_island(my_scene);
    }
}

void reset_game_scene(game_scene* scene) {
    for (int i = 0; i < scene->enemy_count; i++)
    {
        reset_enemy(scene->enemies[i]);
    }

    for (int i = 0; i < scene->island_count; i++)
    {
        scene->islands[i]->is_active = false;
    }

    reset_player(scene->player);
    change_score_text(scene->hp_bar_rect, scene->max_hp_bar_width, scene->player->score);

    Mix_PlayMusic(audiomgr.bg_music, -1);
}

void draw_title_scene(title_scene* scene, boolean* play, boolean* quit) {

    if(event.type == SDL_MOUSEMOTION)
    {
        SDL_GetMouseState(&scene->rect_mouse_pos->x,&scene->rect_mouse_pos->y);
    }

    SDL_RenderCopy(renderer, scene->texture_bg, NULL, NULL);
    write_title_scene(scene->rect_start_game, scene->rect_quit_game);
    draw_titles();

    // if(SDL_HasIntersection(scene->rect_mouse_pos, scene->rect_start_game)) {
    //     if(event.type == SDL_MOUSEBUTTONDOWN) {
    //         *play = true;
    //     }
    // }
    // else if(SDL_HasIntersection(scene->rect_mouse_pos, scene->rect_quit_game)) {
    //     if(event.type == SDL_MOUSEBUTTONDOWN) {
    //         *quit = true;
    //     }
    // }
}
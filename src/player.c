#include <player.h>
#include <utils.h>
#include <stdio.h>

player* create_player() {
    player* pl = (player*)malloc(sizeof(player));
    pl->actor = (actor*)malloc(sizeof(actor));
    pl->actor->texture = create_texture("resources/assets/player/myplane_strip3.png");
    pl->actor->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    pl->actor->anim_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    pl->texture_death = create_texture("resources/assets/player/explosion2_strip7.png");
    pl->rect_death = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    pl->anim_rect_death = (SDL_Rect*)malloc(sizeof(SDL_Rect));


    // set up the position and the base animation for the player
    pl->actor->rect->w = 65;
    pl->actor->rect->h = 65;
    pl->actor->rect->x = (WINDOW_WIDTH * 0.5f) - pl->actor->rect->w * 0.5f;
    pl->actor->rect->y = (WINDOW_HEIGHT * 0.75f) - pl->actor->rect->h * 0.5f;

    pl->actor->anim_rect->w = 65;
    pl->actor->anim_rect->h = 65;
    pl->actor->anim_rect->x = 0;
    pl->actor->anim_rect->y = 0;

    pl->actor->curr_anim_frame = 0;
    pl->actor->anim_frames = 3;
    pl->actor->max_anim_time = 0.1f;
    pl->actor->curr_anim_time = 0;
    

    // set up the death_animation
    pl->death_curr_anim_frame = 0;
    pl->death_anim_frames = 8;
    pl->death_max_anim_time = 0.1f;
    pl->death_curr_anim_time = 0.f;

    pl->rect_death->w = 65;
    pl->rect_death->h = 65;
    pl->anim_rect_death->w = 65;
    pl->anim_rect_death->h = 65;
    pl->anim_rect_death->x = 0;
    pl->anim_rect_death->y = 0;


    pl->actor->speed = -200.f;
    pl->actor->max_health = 100;
    pl->actor->health = pl->actor->max_health;

    pl->lifes = 4;
    pl->bullets_count = 10;
    pl->score = 0;
    
    pl->bullets = (player_bullet**)malloc(pl->bullets_count * sizeof(player_bullet*));

    for (int i = 0; i < pl->bullets_count; i++)
    {
        pl->bullets[i] = (player_bullet*)malloc(sizeof(player_bullet));
        pl->bullets[i] = create_player_bullet();
    }

    pl->default_shoot_cd = 0.5f;
    pl->shoot_cd = pl->default_shoot_cd;
    pl->default_invulnerability_cd = 2.f;
    pl->invulnerability_cd = 0;

    pl->is_alive = true;
    pl->is_invulnerable = false;

    return pl;
}

void player_take_damage(player* player, float damage) {
    player->actor->health -= damage;

    if(player->is_alive && player->actor->health <= 0) {
        player->lifes -= 1;
        player->is_invulnerable = true;
        player->actor->health = 0;
        
        if(player->lifes == 0) {
            player->is_alive = false;
            player->is_dead = true;

            player->rect_death->x = player->actor->rect->x;
            player->rect_death->y = player->actor->rect->y;

            Mix_PlayChannel(-1, audiomgr.player_explosion, 0);
            return;
        }
        player->actor->health = player->actor->max_health;
    }
}

void player_input(player* pl) {
    player_movement_input(pl->actor->rect, pl->actor->speed);
    // check for shoot
    if (keyboard_state[SDL_SCANCODE_X] || keyboard_state[SDL_SCANCODE_SPACE]) {
        for (int i = 0; i < pl->bullets_count; i++)
        {
            if(!pl->bullets[i]->bullet->is_active) {
                if(pl->shoot_cd >= pl->default_shoot_cd){
                    pl->shoot_cd = 0; 
                    player_shoot_input(pl->bullets[i]->bullet, pl->actor->rect, pl->actor->speed);
                    break;
                }
            }
        }
    }
    pl->shoot_cd += delta_time;
}

void check_player_bounds(SDL_Rect* player_rect) {
    if(player_rect->x < 0) {
        player_rect->x = 0;
    }
    else if(player_rect->x > WINDOW_WIDTH - player_rect->w) {
        player_rect->x = WINDOW_WIDTH - player_rect->w;
    }

    if(player_rect->y < 0) {
        player_rect->y = 0;
    }
    else if(player_rect->y > (WINDOW_HEIGHT - BOTTOM_UI_ELEMENT_HIGHT_SCREEN) - player_rect->h) {
        player_rect->y = (WINDOW_HEIGHT - BOTTOM_UI_ELEMENT_HIGHT_SCREEN) - player_rect->h;
    }
}

void update_player_bullets(player* pl){
    for (int i = 0; i < pl->bullets_count; i++)
    {   
        if(pl->bullets[i]->bullet->is_active) {
            update_bullets_pos(pl->bullets[i]->bullet);
        }
    }
}

void draw_player(player* player) {
    if(player->is_invulnerable) {
        int player_frames = 5;
        animate_rect(player->actor->anim_rect, &player_frames, &player->actor->curr_anim_frame, &player->actor->max_anim_time, &player->actor->curr_anim_time);
        player->invulnerability_cd += delta_time;

        if(player->invulnerability_cd >= player->default_invulnerability_cd) {
            player->invulnerability_cd -= player->default_invulnerability_cd;
            player->is_invulnerable = false;
        }
    }
    else {
        animate_rect(player->actor->anim_rect, &player->actor->anim_frames, &player->actor->curr_anim_frame, &player->actor->max_anim_time, &player->actor->curr_anim_time);
    }
    if(player->is_invulnerable) {
        if (!player->blink) {
            SDL_RenderCopy(renderer, player->actor->texture, player->actor->anim_rect, player->actor->rect);
            player->blink = true;
        }
        else
            player->blink = false;        
    }
    else
        SDL_RenderCopy(renderer, player->actor->texture, player->actor->anim_rect, player->actor->rect);
}

void update_player_death(player* pl) {
    animate_rect(pl->anim_rect_death, &pl->death_anim_frames, &pl->death_curr_anim_frame, &pl->death_max_anim_time, &pl->death_curr_anim_time);
    SDL_RenderCopy(renderer, pl->texture_death, pl->anim_rect_death, pl->rect_death);
    if(pl->death_curr_anim_frame == pl->death_anim_frames - 1) {
        pl->is_dead = false;
        pl->death_curr_anim_frame = 0;
    }
}

void update_player(player* pl) {
    if(pl->is_alive) {
        if(!pl->is_invulnerable) {
            // pick up player input
            player_input(pl);
        }
        // draw bullets
        update_player_bullets(pl);
        // draw player
        draw_player(pl);
        check_player_bounds(pl->actor->rect);
    }
    else if(pl->is_dead) {
        update_player_death(pl);
    }
}

void reset_player(player* pl) {
    if(!pl->is_alive && !pl->is_dead) {
        // set up the position and the base animation for the player
        pl->actor->rect->x = (WINDOW_WIDTH * 0.5f) - pl->actor->rect->w * 0.5f;
        pl->actor->rect->y = (WINDOW_HEIGHT * 0.75f) - pl->actor->rect->h * 0.5f;

        pl->actor->curr_anim_frame = 0;

        pl->lifes = 4;
        pl->score = 0;
        pl->actor->health = pl->actor->max_health;

        for (int i = 0; i < pl->bullets_count; i++)
        {
            pl->bullets[i]->bullet->is_active = false;
        }

        pl->is_alive = true;
        pl->is_invulnerable = false;
        pl->is_dead = false;
    }
}
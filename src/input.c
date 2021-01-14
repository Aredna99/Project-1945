#include <input.h>

void player_movement_input(SDL_Rect* rect, float speed) {
    //keyboard_state = SDL_GetKeyboardState(NULL);
    if (keyboard_state[SDL_SCANCODE_UP]) {
        rect->y += (int)(speed * delta_time);
    }
    if (keyboard_state[SDL_SCANCODE_DOWN]) {
        rect->y -= (int)(speed * delta_time);
    }

    if (keyboard_state[SDL_SCANCODE_LEFT]) {
        rect->x += (int)(speed * delta_time);
    } 
    if (keyboard_state[SDL_SCANCODE_RIGHT]) {
        rect->x -= (int)(speed * delta_time);
    }
}

void player_shoot_input(bullet* pl_bullet, SDL_Rect* pl, float speed) {
    pl_bullet->is_active = true;

    pl_bullet->rect->x = pl->x + (pl->w / 2) - (pl_bullet->rect->w / 2);
    pl_bullet->rect->y = pl->y - pl_bullet->rect->h / 2;

    pl_bullet->speed = speed - 100.f;
}
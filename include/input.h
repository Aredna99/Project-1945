#ifndef INPUT_H
#define INPUT_H
#include <render_mgr.h>
#include <bullet.h>

void player_movement_input(SDL_Rect* rect, float speed);
void player_shoot_input(bullet* pl_bullet, SDL_Rect* pl, float speed);

#endif
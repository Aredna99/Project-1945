#ifndef ACTOR_H
#define ACTOR_H
#include <render_mgr.h>
#include <time.h>
#include <stdlib.h>
#include <utils.h>

typedef struct {
    SDL_Texture* texture;
    SDL_Rect* rect;
    SDL_Rect* anim_rect;
    int anim_frames;            //number of frame for the caracther_sheet in the same row
    int curr_anim_frame;        //actual frame of the character_sheet 
    float max_anim_time;        //time for change frame
    float curr_anim_time;       //
    float speed;
    int max_health;
    int health;
    float collider_radius;
} actor;

int change_image(SDL_Rect* rect, int* anim_frame);
void animate_rect(SDL_Rect* rect, int* max_frames, int* curr_frame, float* max_time, float* curr_time);

#endif
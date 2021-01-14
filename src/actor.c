#include "actor.h"
#include <stdio.h>
#include <utils.h>

int change_image(SDL_Rect* rect, int* anim_frame) {
    *anim_frame += 1;
    /*if(*anim_frame > 2) {
        *anim_frame = 0;
    }*/

    rect->x = *anim_frame * rect->w;

    return *anim_frame;
}

void animate_rect(SDL_Rect* rect, int* max_frames, int* curr_frame, float* max_time, float* curr_time) {
    
    *curr_time += delta_time;

    if (*curr_time >= *max_time) {
        *curr_time -= *max_time;
        change_image(rect, curr_frame);

        if(*curr_frame >= *max_frames) {
            *curr_frame = 0;
        }

        rect->x = *curr_frame * rect->w;
    }
}
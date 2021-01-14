#ifndef ACTOR_H
#define ACTOR_H
#include <render_mgr.h>
#include <time.h>
#include <stdlib.h>
#include <utils.h>

typedef struct {
    SDL_Texture* texture;       //Texture of the object
    SDL_Rect* rect;             //Rect for the position of the object
    SDL_Rect* anim_rect;        //Rect for render the animation
    int anim_frames;            //Number of frame for the caracther_sheet in the same row
    int curr_anim_frame;        //Actual frame of the animation 
    float max_anim_time;        //Time for change frame
    float curr_anim_time;       //Current time of the animation
    float speed;                //Speed for move the object
    int max_health;             //Max health of the object
    int health;                 //Actual health of the object
} actor;

int change_image(SDL_Rect* rect, int* anim_frame);
void animate_rect(SDL_Rect* rect, int* max_frames, int* curr_frame, float* max_time, float* curr_time);

#endif
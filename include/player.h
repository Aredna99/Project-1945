#ifndef PLAYER_H
#define PLAYER_H
#include "actor.h"
#include "input.h"
#include "bullet.h"

typedef struct {
    actor* actor;
    player_bullet** bullets;                    //array of player_bullets

    SDL_Texture* texture_death;                 //texture when the player die
    SDL_Rect* anim_rect_death;                  //render the anim of the dead player
    SDL_Rect* rect_death;                       //position where renderer the dead player

    boolean is_alive;                           //check if the player can continue to play or not
    boolean is_dead;                            //check if start the death animation
    boolean is_invulnerable;                    //check if the player is hittable from the objects
    boolean blink;                              //check if the player is renderer or not

    int death_anim_frames;                      //number of frame for the caracther_sheet in the same row
    int death_curr_anim_frame;                  //actual frame of the character_sheet 
    float death_max_anim_time;                  //time for change frame
    float death_curr_anim_time;                 //

    int bullets_count;                          //max number of bullets that can be draw in the same frame
    int lifes;                                  //number of lifes
    int score;                                  //score of the player
    float default_shoot_cd;                     //time which bullet can be shooted is succession from the player
    float shoot_cd;                             //variable that increase with delta_time till reach the default_shoot_cd variable 
    float default_invulnerability_cd;           //time of invulnerability for the player
    float invulnerability_cd;                   //time before return vulnerable
} player;

player* create_player();
void player_input();
void check_player_bounds(SDL_Rect* pos_rect);
void update_player(player* player); 
void update_player_bullets(player* player);
void player_take_damage(player* player, float damage);
void draw_player(player* player);
void reset_player(player* player);
void update_player_death(player* player);
void destroy_player(player* player);

#endif

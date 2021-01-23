#ifndef ENEMY_H
#define ENEMY_H
#include "actor.h"
#include "bullet.h"

typedef struct {
    actor* actor;
    enemy_bullet** bullets;
    boolean is_active;
    boolean is_dead;                    //Check if start the death animation
    SDL_Texture* texture_death;         //Texture when the enemy die
    SDL_Rect* anim_rect_death;          //Render the anim of the dead enemy
    SDL_Rect* rect_death;               //Position where renderer the dead enemy

    int death_anim_frames;              //Number of frame for the caracther_sheet in the same row
    int death_curr_anim_frame;          //Actual frame of the character_sheet 
    float death_max_anim_time;          //Time for change frame
    float death_curr_anim_time;         //Current time for the update of death animation

    int body_damage;                    //Damage inflictet on collision with the player
    int bullets_count;                  //Max number of active bullets that the enemy can have in the same frame 
    int score;                          //Points awarded to the player on the death of this enemy 
    float default_shoot_cd;             //Time variable wich enemy can shoot
    float shoot_cd;                     //Time before can shoot
} enemy;

enemy* create_enemy();
void reset_enemy(enemy* en);
void set_enemy_spawnpoint(SDL_Rect* rect);
void instantiate_enemy(enemy* en);
void enemy_ready_to_shoot(enemy* en);
void enemy_shoot(enemy* enemy, bullet* bullet);
void check_enemy_bounds(enemy* pos_rect);
void update_enemy_movement(enemy* en); 
void update_enemy_bullets(enemy* en);
void update_enemy(enemy* en); 
void enemy_take_damage(enemy* enemy, float damage);
void update_enemy_death(enemy* enemy);
void destroy_enemy(enemy* enemy);

#endif
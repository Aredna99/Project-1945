#ifndef ISLAND_H
#define ISLAND_H
#include "actor.h"

typedef struct {
    actor* actor; 
    boolean is_active;
} island;

island* create_island();
void set_island_spawnpoint(island* island);
void instantiate_island(island* island);
void island_movement(island* island);
void check_island_bounds(island* island);
void update_island(island* island);

#endif
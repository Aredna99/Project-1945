#include <island.h>

island* create_island() {
    island* new_island = (island*)malloc(sizeof(island));
    new_island->actor = (actor*)malloc(sizeof(actor));
    new_island->actor->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

    int rnd = rand() % 3 + 1;

    if(rnd == 1) {
        new_island->actor->texture = create_texture("resources/assets/map/island1.png");
        new_island->actor->rect->h = 57;
        new_island->actor->rect->w = 50;
    }
    else if(rnd == 2) {
        new_island->actor->texture = create_texture("resources/assets/map/island2.png");
        new_island->actor->rect->h = 68;
        new_island->actor->rect->w = 64;
    }
    else {
        new_island->actor->texture = create_texture("resources/assets/map/island3.png");
        new_island->actor->rect->h = 46;
        new_island->actor->rect->w = 46;
    }

    set_island_spawnpoint(new_island);
    new_island->actor->speed = 150;
    new_island->is_active = false;

    return new_island;
}

void set_island_spawnpoint(island* island) {
    island->actor->rect->x = rand() % (WINDOW_WIDTH - island->actor->rect->w);
    island->actor->rect->y = -island->actor->rect->h;
}

void instantiate_island(island* island) {
    set_island_spawnpoint(island);
    island->is_active = true;
}

void island_movement(island* island) {
    island->actor->rect->y += (int)(island->actor->speed * delta_time);
}

void check_island_bounds(island* island) {
    if(island->actor->rect->y > WINDOW_HEIGHT - BOTTOM_UI_ELEMENT_HIGHT_SCREEN) {
        island->is_active = false;
    }
}

void update_island(island* island) {
    if(island->is_active) {
        island_movement(island);
        SDL_RenderCopy(renderer, island->actor->texture, NULL, island->actor->rect);
        check_island_bounds(island);
    }
}

void destroy_island(island* island) {
    free(island->actor->rect);
    free(island->actor);
    free(island);
}
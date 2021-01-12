#include "render_mgr.h"

void create_window() {
    window = SDL_CreateWindow(
        "1945",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        0
    );

    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s\n", SDL_GetError());
        return;
    }
}

void create_renderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s\n", SDL_GetError());
        return;
    }
}

SDL_Texture* create_texture(char* filepath) {
    SDL_Surface* png_surface = IMG_Load(filepath);
    if(png_surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load surface: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Texture* png_texture = SDL_CreateTextureFromSurface(renderer, png_surface);

    return png_texture;
} 
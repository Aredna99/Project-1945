#ifndef RENDER_MGR_H
#define RENDER_MGR_H
#include <SDL.h>
#include <SDL_image.h>

enum boolean_enum { false, true };
typedef unsigned char boolean;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BOTTOM_UI_ELEMENT_HIGHT_SCREEN 76

SDL_Window* window;
SDL_Renderer* renderer;

typedef struct{
    SDL_Texture* texture;
    SDL_Rect* rect;
} sprite;

void create_window();
void create_renderer();
SDL_Texture* create_texture(char* filepath);

#endif
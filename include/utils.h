#ifndef UTILS_H
#define UTILS_H
#include "SDL.h"
#include "SDL_image.h"
#include "render_mgr.h"
#include "audio_mgr.h"
#include "font_mgr.h"

char title[100];
float delta_time;
float update_time;
int fps;
Uint64 curr_count;
Uint64 last_count;
Uint8* keyboard_state;

void init_utils();
void update_utils(boolean* done);

#endif
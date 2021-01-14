#include <utils.h>

void init_utils() {
    curr_count = SDL_GetPerformanceCounter();
    last_count = curr_count;
    Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
}

void update_utils(boolean* done) {
    //SDL_Event event;
        // while (SDL_PollEvent(&event)) {
        //     if (event.type == SDL_QUIT) {
        //         *done = true;
        //         break;
        //     }
        //     else if(event.key.keysym.sym == SDLK_ESCAPE) {
        //         *done = true;
        //         break;
        //     }
        // }

    keyboard_state = SDL_GetKeyboardState(NULL);
    last_count = curr_count;
    curr_count = SDL_GetPerformanceCounter();
    delta_time = (float)(curr_count - last_count) / (float)SDL_GetPerformanceFrequency();
    fps = (int)(1.f / delta_time);
    update_time += delta_time;

    if (update_time >= 1.f) {
        update_time -= 1.f;
        sprintf_s(title, sizeof(title), "1945 game!");
        SDL_SetWindowTitle(window, title);
    }
}
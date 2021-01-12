#ifndef AUDIO_MGR_H
#define AUDIO_MGR_H
#include <SDL.h>
#include <SDL_mixer.h>


typedef struct 
{
    Mix_Music* bg_music;
    Mix_Chunk* explosion_1;
    Mix_Chunk* player_explosion;

} audio_mgr;

audio_mgr audiomgr;


void init_audiomgr(audio_mgr* audiomgr);

#endif
#include <audio_mgr.h>

void init_audiomgr(audio_mgr* audiomgr){
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 2048);

    audiomgr->bg_music = Mix_LoadMUS("resources/assets/audio/background.mp3");
    audiomgr->explosion_1 = Mix_LoadWAV("resources/assets/audio/snd_explosion1.wav");
    audiomgr->player_explosion = Mix_LoadWAV("resources/assets/audio/snd_explosion2.wav");

    //Mix_PlayMusic(audiomgr->bg_music, -1);
}
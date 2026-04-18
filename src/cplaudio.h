#ifndef CPL_AUDIO_H
#define CPL_AUDIO_H
#include "cpl.h"

csound_t* csnd_load_wav(char* buffer, int size);

/*
 * 1 - right
 * 2 - left
 * 
 */
void csnd_playsound(const csound_t sound, char mode);

csound_t* csnd_Y1();

#endif // !CPL_AUDIO_H
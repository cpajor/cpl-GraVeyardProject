#ifndef CPL_AUDIO_H
#define CPL_AUDIO_H
#include "cpl.h"
#include <Windows.h>

typedef struct csound_s {
    WAVEFORMATEX wfx;
    const BYTE* data;
    DWORD dataSize;
} csound_t;

void csnd_playsound(csound_t snd);
 
csound_t* csnd_load(unsigned char* buffer, unsigned long long size);

csound_t y1csound();

#endif // !CPL_AUDIO_H
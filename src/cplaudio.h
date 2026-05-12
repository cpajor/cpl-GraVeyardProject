#ifndef CPL_AUDIO_H
#define CPL_AUDIO_H
#include "cpl.h"
#include <Windows.h>
#include <xaudio2.h> 

#define CSOUND_FX 0
#define CSOUND_MUSIC 1

typedef struct csound_s {
    WAVEFORMATEX wfx;
    const BYTE* data;
    DWORD dataSize;
    char type;
} csound_t;

typedef struct csoundcallback_s {
    IXAudio2SourceVoice* voice;
    char type;
} csoundcallback_t; 

void csnd_playsound(csound_t snd);
void csnd_playsoundc(csound_t snd, csoundcallback_t *callback);
void csnd_stopsound(csoundcallback_t snd);

csound_t* csnd_load(unsigned char* buffer, size_t size);
csound_t y1csound();
csound_t y1csoundt(char type);

#endif // !CPL_AUDIO_H
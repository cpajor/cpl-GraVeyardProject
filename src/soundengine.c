#include "cplaudio.h"

#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "winmm.lib")

typedef struct wavstr_s {
    WAVEHDR header;
    HWAVEOUT hwav; //handle
} wavstr_t;

wavstr_t *hWait[64];

void csnd_stop(wavstr_t s) {
    waveOutUnprepareHeader(s.hwav, &s.header, sizeof(WAVEHDR));
    waveOutClose(s.hwav);
}

void csnd_add(wavstr_t s) {
    for (int i = 0; i < 64; i++) {
        if (hWait[i] == 0) {
            hWait[i] = &s;
            return;
        }
    } 
    csnd_stop(s); // sound num overflow
}

void csnd_playsound(const csound_t sn, char mode) {
    WAVEFORMATEX wfx;
    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = 2;
    wfx.nSamplesPerSec = sn.sampleRate;
    wfx.wBitsPerSample = 16;
    wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) / 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

    HWAVEOUT hWaveOut;
    if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) return;
    
    short* dat = sn.data;
    
    /* TODO STEREO
    */

    WAVEHDR header;
    header.lpData = (LPSTR)dat;
    header.dwBufferLength = sn.samples;

    if (waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        waveOutClose(hWaveOut);
        return;
    }

    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    csnd_add((wavstr_t){ header, hWaveOut });
}

void _csnd_thr() {
    Sleep(50);
    for (int i = 0; i < 64; i++) {
        if (hWait[i] != 0) 
        if (!(hWait[i]->header.dwFlags & WHDR_DONE)) {
            csnd_stop(*hWait[i]);
            hWait[i] = 0;
        }
    }
}

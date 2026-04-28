#include "cplaudio.h"

#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "winmm.lib")

csound_t* _snd_queue[64];

void csound_init() {
    for (int i = 0; i < 64; i++) {
        _snd_queue[i] = 0;
    }
}

DWORD WINAPI csound_async(LPVOID param) {
    int id = param;

    csound_t* se = _snd_queue[id];

    WAVEFORMATEX wfx;
    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = se->channels;
    wfx.nSamplesPerSec = se->sampleRate;
    wfx.wBitsPerSample = 16;
    wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) / 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
    
    HANDLE hEvent = CreateEventW(0, FALSE, FALSE, 0);

    HWAVEOUT hWaveOut;
    if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, (DWORD_PTR)hEvent, 0, CALLBACK_EVENT) != MMSYSERR_NOERROR) {
        CloseHandle(hEvent);
        return 0;
    }

    WAVEHDR header;
    ZeroMemory(&header, sizeof(WAVEHDR));
    header.dwBufferLength = se->samples;
    header.lpData = malloc(header.dwBufferLength);
    memcpy(header.lpData, se->data, header.dwBufferLength);

    if (waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        waveOutClose(hWaveOut);
        CloseHandle(hEvent);
        return 0;
    }

    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    WaitForSingleObject(hEvent, INFINITE);

    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));

    free(header.lpData);

    waveOutClose(hWaveOut);

    CloseHandle(hEvent);

    _snd_queue[id] = 0;

    return 0;
}

void csnd_playsound(const csound_t* sn) {
    int pos = -1;
    // fixed, direct variable causes crash (XD)
    for (int i = 0; i < 1; i++) {
        if (_snd_queue[i] == 0) {
            pos = i;
            _snd_queue[i] = sn;
        }
    }

    if (pos < 0) return;

    HANDLE c = CreateThread(NULL, 0, csound_async, pos, 0, NULL);
    // TODO

}
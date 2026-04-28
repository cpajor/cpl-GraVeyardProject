#include "cplaudio.h"
#include "cpl.h"

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* y1cbuf; // mem.c
extern int y1csiz; // mem.c

int _read_int32(char* buffer) {
    unsigned char* b = (unsigned char*)buffer;
    return b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
}

short _read_int16(char* buffer) {
    unsigned char* b = (unsigned char*)buffer;
    return (short)(b[0] | (b[1] << 8));
}

csound_t* csnd_load_wav(char* buffer, int size) {
    if (buffer == 0 || size < 44) return 0;

    if (strncmp(buffer, "RIFF", 4) != 0 || strncmp(buffer + 8, "WAVE", 4) != 0) return 0; 
    
    int offset = 12; 
    int sampleRate = 0;
    int bitsPerSample = 0;
    int dataSize = 0;
    char* audioData = 0;
    short numChannels = 1; // fix

    while (offset < size - 8) {
        char chunkId[5];
        strncpy(chunkId, buffer + offset, 4);
        chunkId[4] = '\0';

        int chunkSize = _read_int32(buffer + offset + 4);
        offset += 8; 

        if (strcmp(chunkId, "fmt ") == 0) {
            if (chunkSize < 16) return 0;

            short audioFormat = _read_int16(buffer + offset);
            if (audioFormat != 1) return 0; 

            numChannels = _read_int16(buffer + offset + 2);

            // idk why works only if theres separeted function XD
            sampleRate = _read_int32(buffer + offset + 4);
            bitsPerSample = _read_int16(buffer + offset + 14);

            if (bitsPerSample != 16) return 0;
            
        }
        else if (strcmp(chunkId, "data") == 0) {
            dataSize = chunkSize;

            if (offset + dataSize > size) {
                dataSize = size - offset;
            }

            audioData = (char*)malloc(dataSize);

            memcpy(audioData, buffer + offset, dataSize);

            break; 
        }

        offset += chunkSize;
    }

    if (audioData == 0 || sampleRate == 0) return 0;
    
    csound_t* sound = malloc(sizeof(csound_t));

    /*
        TODO STEREO

    for (int i = 0; i < sampleRate; i += 2) {
        if (dat[i] == 0) {

        }
        if (dat[i + 1] == 0 && dat[i] > 0) {

        }
    }
    */

    sound->samples = dataSize;
    sound->sampleRate = sampleRate;
    sound->data = audioData;
    sound->channels = numChannels;

    return sound;
}

csound_t* csnd_Y1() {
    return csnd_load_wav(y1cbuf, y1csiz);
}
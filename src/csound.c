#include "cplaudio.h"
#include "cplthread.h"

#include <stdlib.h>
#pragma comment(lib, "xaudio2.lib")

extern char* y1cbuf;
extern int y1csiz;

IXAudio2* g_xaudio;
IXAudio2MasteringVoice* g_master;

/* 
void csnd_playsound(const csound snd) {
	PlaySound((LPCSTR)snd, NULL, SND_MEMORY | SND_ASYNC); // crash when RIFF is broken !!
	 * https://pl.wikipedia.org/wiki/WAV
	 * Author note:
	 *
	 * win32 api (mmsystem) ma wbudowany loader i player .WAV, zanim sie dowiedzialem o tym, pisalem, potem cala robota poszla w dupe, glownie dlatego, ze thread postanawial robic memory leak dla zabawy
	 * po uzyciu tego kodu co jest i sprawdzeniu ze wszystko dziala stwierdzilem ze pierdole to, gdyz:
	 * - pisalem 3 razy od zera loader WAV.
	 * - spedzilem cale noce nad naprawianiem jebanego memory leaku
	 * - SIX SEVEM
	 *
}
 
PS: Radosc nie trwala zbyt dlugo, gdyz mozna odpalic tylko 1 wav na raz XD
*/

void csnd_init() {
	HRESULT hr;

	CoInitializeEx(0, COINIT_MULTITHREADED);

	hr = XAudio2Create(&g_xaudio, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr)) {
		// TODO exit(1);
		return;
	}
	hr = g_xaudio->lpVtbl->CreateMasteringVoice(g_xaudio, &g_master, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, 0, AudioCategory_GameEffects);
}

void csnd_playsoundc(csound_t snd, csoundcallback_t* callback) {
	if (snd.dataSize == 0) return;

	IXAudio2SourceVoice* voice = 0;

	HRESULT hr = g_xaudio->lpVtbl->CreateSourceVoice(g_xaudio, &voice, &snd.wfx, 2, XAUDIO2_DEFAULT_FREQ_RATIO, 0, 0, 0);

	if (FAILED(hr))
		return;

	// fix
	XAUDIO2_BUFFER buf;
	memset(&buf, 0, sizeof(buf));

	buf.AudioBytes = snd.dataSize;
	buf.pAudioData = snd.data;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	voice->lpVtbl->SubmitSourceBuffer(voice, &buf, 0);
	voice->lpVtbl->Start(voice, 0, XAUDIO2_COMMIT_NOW);

	if (callback) {
		*callback = (csoundcallback_t) { voice, snd.type };
	}
}

void csnd_playsound(csound_t snd) {
	csnd_playsoundc(snd, 0);
}

void csnd_stopsound(csoundcallback_t snd) {
	if (snd.type < 0) return;
	if (snd.voice) {
		snd.voice->lpVtbl->Stop(snd.voice, 0, XAUDIO2_COMMIT_NOW);
	}
	snd.type = -1;
}

csound_t* csnd_load(unsigned char* buffer, size_t size) {
	// dont remove 'const' / size_t - fix
	const unsigned char* ptr = buffer;
	const unsigned char* end = buffer + size;

	// fix 
	csound_t* snd = malloc(sizeof(csound_t));

	if (size < 12) return 0;
	if (memcmp(ptr, "RIFF", 4) != 0) return 0;
	ptr += 8;
	
	if (memcmp(ptr, "WAVE", 4) != 0) return 0;
	ptr += 4;

	int foundFmt = 0;
	int foundData = 0;
	while (ptr + 8 <= end) {
		char chunkId[4];
		memcpy(chunkId, ptr, 4);
		ptr += 4;

		unsigned int chunkSize = *(unsigned int*)ptr;
		ptr += 4;

		if (ptr + chunkSize > end)
			return 0;

		if (memcmp(chunkId, "fmt ", 4) == 0) {
			memset(&snd->wfx, 0, sizeof(WAVEFORMATEX));

			memcpy(&snd->wfx, ptr, chunkSize < sizeof(WAVEFORMATEX) ? chunkSize : sizeof(WAVEFORMATEX));

			foundFmt = 1;
		}
		if (memcmp(chunkId, "data", 4) == 0) {
			snd->dataSize = chunkSize;
			snd->data = malloc(chunkSize);
			memcpy(snd->data, ptr, chunkSize);
			foundData = 1;
		}

		ptr += (chunkSize + 1) & ~1;
	}

	if (!(foundFmt && foundData)) {
		return 0;
	}
	return snd;
}

csound_t y1csound() {
	return y1csoundt(CSOUND_FX);
}

csound_t y1csoundt(char type) {
	csound_t c = *csnd_load(y1cbuf, y1csiz);
	c.type = type;
	return c;
}
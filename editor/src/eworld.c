#include "cplworld.h"
#define CPL_MAGIC1 0xBADA55
#define CPL_MAGIC2 0xBADC0DE

int currentSeed;

wchunk_t* w_chunks;
size_t w_chunksSize;
int w_palette;
pos_t w_start;

int wSeedNext(int in) {
	return (in * 11) % CPL_MAGIC1;
}

void w_init() {
	currentSeed = wSeedNext(CPL_MAGIC2);
}

edict_t* enewEdict() {
	edict_t edic[64];

	for (int i = 0; i < 64; i++) {
		edic[i] = (edict_t){ 0x100, 0, 0x100 };
	}

	return edic;
}

edict_t* ewgetEdict(int pos) {
	if (pos < 0) return 0;
	if (pos > w_chunksSize - 1) return 0;
	//
	return w_chunks[pos].edicts;
}
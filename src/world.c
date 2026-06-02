#include "cplworld.h"
#define CPL_MAGIC1 0xBADA55
#define CPL_MAGIC2 0xBADC0DE

int currentSeed;
wchunk_t* currentScene;

pos_t wpos(int x, int y) {
	return (pos_t) { x, y };
}

char wposcmp(pos_t b1, pos_t b2) {
	return b1.x == b2.x && b1.y == b2.y;
}

int wSeedNext(int in) {
	return (in * 11) % CPL_MAGIC1;
}

void w_init() {
	currentSeed = wSeedNext(CPL_MAGIC2);
}

edict_t* wgetEdict(int pos) {
	// TODO
	edict_t edic[64];

	for (int i = 0; i < 64; i++) {
		edic[i] = (edict_t) { 0, 0, 0 };
		if (i == 0) {
			edic[i] = (edict_t) { 0x102, 1, 0 };
		}
	}

	//

	return edic;
}
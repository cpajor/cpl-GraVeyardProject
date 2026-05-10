#include "cpl.h"
#include "cplworld.h"
#define CPL_MAGIC1 0xBADA55
#define CPL_MAGIC2 0xBADC0DE

int currentSeed;
wchunk_t currentScene;

location_t wlocation(double x, double y) {
	return (location_t) { x, y, 0 };
}

location_t wlocationb(pos_t b) {
	return (location_t) { b.x, b.y, 0 };
}

pos_t wblockpos(location_t l) {
	return (pos_t) { l.x, l.y };
}

char wlocationcmp(pos_t b1, pos_t b2) {
	return b1.x == b2.x && b1.y == b2.y;
}

int wSeedNext(int in) {
	return (in * 11) % CPL_MAGIC1;
}

void w_init() {
	currentSeed = wSeedNext(CPL_MAGIC2);
}

wchunk_t genChunk() {
	wchunk_t chunk;


	return chunk;
}

edict_t* wgetEdict(pos_t pos) {


	return 0;
}
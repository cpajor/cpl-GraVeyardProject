#include "cplworld.h"
#define CPL_MAGIC1 0xBADA55
#define CPL_MAGIC2 0xBADC0DE

int currentSeed;

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


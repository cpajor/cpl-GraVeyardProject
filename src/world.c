#include "cpl.h"
#include "cplworld.h"

int currentSceneId;
wscene_t currentScene;

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

void w_init() {

}

edict_t* wgetEdict(pos_t pos) {


	return 0;
}
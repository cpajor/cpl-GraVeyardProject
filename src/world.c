#include "cplworld.h"
#include "ginput.h"
#define CPL_MAGIC1 0xBADA55
#define CPL_MAGIC2 0xBADC0DE

#include <stdio.h>

extern void player_tick();

extern char _ginput[11];
extern pos_t player_pos;

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

edict_t* ewgetEdict(int pos) {
	if (pos < 0) return 0;
	if (pos > w_chunksSize - 1) return 0;
	//
	return w_chunks[pos].edicts;
}

int caworld_getType(int x, int y) {
	if (x < 0 || x > w_chunksSize - 1 || y < 0 || y > 63) return 100;
	return w_chunks[x].edicts[y].type;
}

void caworld_setCollide(int x, int y, char collide) {
	if (x < 0 || x > w_chunksSize - 1 || y < 0 || y > 63) return;
	w_chunks[x].edicts[y].collide = collide;
}

char player_checkTile(int type) {
	if (type == 100) return 1;
	if (type == 110) return 1;


	return 0;
}

char player_canMove(int x, int y) {
	int left = (x - 40) / 40;
	int right = (x + 40 - 1) / 40;

	int top = y / 40;
	int bottom = (y + 80 - 1) / 40;

	for (int tx = left; tx <= right; tx++) {
		for (int ty = top; ty <= bottom; ty++) {
			if (player_checkTile(caworld_getType(tx, ty))) return 0;
		}
	}

	return 1;
}

void caworld_tick() {
	if (_ginput[CKEY_LEFT]) {
		if (player_canMove(player_pos.x - 10, player_pos.y)) {
			player_pos.x -= 10;
			player_updateView();
		}
	}
	if (_ginput[CKEY_RIGHT]) {
		if (player_canMove(player_pos.x + 10, player_pos.y)) {
			player_pos.x += 10;
			player_updateView();
		}
	}
	player_tick();
}

char caworld_onground() {
	return !player_canMove(player_pos.x, player_pos.y - 1);
}
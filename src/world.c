#include "cplworld.h"
#include "ginput.h"
#define CPL_MAGIC1 0xBADA55
#define CPL_MAGIC2 0xBADC0DE

#include <stdio.h>

extern void player_tick();
extern char player_direction;
extern pos_t player_pos;
extern char player_walk;
extern char player_attacking;

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
	player_updateView();
	char walk = 0;
	if (cpl_ginput(CKEY_LEFT)) {
		player_direction = 1;
		if (player_attacking == 0) {
			walk = 1;
			if (player_canMove(player_pos.x - 2, player_pos.y)) {
				player_pos.x -= 2;
			}
		}
	}
	if (cpl_ginput(CKEY_RIGHT)) {
		player_direction = 0;
		if (player_attacking == 0) {
			walk = 1;
			if (player_canMove(player_pos.x + 2, player_pos.y)) {
				player_pos.x += 2;
			}
		}
	}
	player_walk = walk;
	player_tick();
	player_updateView(); // 2nd for smooth
}

char caworld_onground() {
	return !player_canMove(player_pos.x, player_pos.y - 1);
}
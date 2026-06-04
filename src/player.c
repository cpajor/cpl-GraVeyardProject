#include "cplworld.h"
#include <math.h>
#define M_RAD (3.14159F / 180.0f)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern wchunk_t* w_chunks;
extern size_t w_chunksSize;
extern pos_t w_start;

pos_t player_pos;
float player_yFactor1;
char player_yFactor2;

CTICK _viewUpLast = 0;

void player_checkVisible(int x, int y, int steps, int dir) {
	w_chunks[x].edicts[y].collide = 1;

	int type = caworld_getType(x, y);

	if (player_checkTile(type)) return;
	
	/*
	2 # 1	
	#####
	3 # 4
	*/
	if (steps) {
		if (y > 0 && (dir == 3 || dir == 4)) {
			player_checkVisible(x	, y - 1	, steps - 3, dir);
		}
		if (y < 62 && (dir == 2 || dir == 1)) {
			player_checkVisible(x	, y + 1	, steps - 3, dir);
		}
		if (x > 0 && (dir == 3 || dir == 2)) {
			player_checkVisible(x - 1, y	, steps - 2, dir);
		}
		if (x < w_chunksSize - 1 && (dir == 1 || dir == 4)) {
			player_checkVisible(x + 1, y	, steps - 2, dir);
		}
	}
}

void player_calcCollide() {
	for (int i = 0; i < w_chunksSize; i++) {
		for (int j = 0; j < 64; j++) {
			w_chunks[i].edicts[j].collide = 0;
		}
	}
	//
	int xp = player_pos.x / 40;
	int yp = player_pos.y / 40;
	for (int i = 1; i < 5; i++) player_checkVisible(xp, yp, 20, i);

	/*
	for (int a = 0; a < 360; a += 5) {
		float rad = a * M_RAD;

		float dx = cosf(rad);
		float dy = sinf(rad);

		pos_t hit = wpos(p_pos.x, p_pos.y + 20);

		while (1) {
			hit.x += dx * 5.0f;
			hit.y += dy * 5.0f;

			int tx = (int)(hit.x / 40);
			int ty = (int)(hit.y / 40);

			if (tx < 0 || ty < 0 || tx >= w_chunksSize || ty >= 64) break;

			w_chunks[tx].edicts[ty].collide = 1;
			if (player_checkTile(w_chunks[tx].edicts[ty].type)) {
				//w_chunks[tx].edicts[ty].collide = 1;
				printf("%i : %i\n", tx, ty);
				break;
			}
		}
	}
	*/
}

void player_tick() {
	caworld_camera(player_pos);
	player_yFactor1 -= 5.F;

	int newY = player_pos.y + (int)player_yFactor1;

	if (player_canMove(player_pos.x, newY)) {
		player_pos.y = newY;

	}
	else {
		player_yFactor1 = 0;

	}
}

void player_updateView() {
	if (_viewUpLast < cplTicks()) {
		_viewUpLast = cplTicks();

	}
	//
	
}

void player_init() {
	//p_pos = wcpy(w_start);
	player_pos = wpos(w_start.x * 40, w_start.y * 40);
}

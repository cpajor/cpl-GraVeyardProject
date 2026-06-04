#include "cplworld.h"
#include "ginput.h"
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
int player_anim;
// 0 - right / 1 - left
char player_direction = 0; 
char player_walk = 0;
char player_attacking = 0;
char player_jumping = 0;
char player_falling = 0;

CTICK _viewUpLast = 0;

void player_updateView() {
	if (_viewUpLast < cplTicks()) {
		_viewUpLast = cplTicks() + 1;
		//
		if (player_jumping) {

		}
		if (player_anim == 25 && player_attacking == 0) {
			player_anim = 1;
		}
		if (player_attacking > 0) {
			if (player_anim < 21) player_anim = 21;
			player_anim++;
			if (player_anim > 24) {
				player_attacking = 0;
				player_anim = 1;
			}
		}
		if (player_walk) {
			player_walk = 0;
			if (player_anim < 10) player_anim = 10;
			player_anim++;
			if (player_anim > 20) player_anim = 10;
		}
		else {
			if (player_anim > 9 && player_anim < 21) player_anim = 1;
		}
		if (player_anim < 9) {
			player_anim++;
			if (player_anim > 8) player_anim = 1;
		}
	}
	//

}

void player_tick() {
	caworld_camera(player_pos);

	player_yFactor1 -= 0.2F;
	
	if (!cpl_ginput(CKEY_JUMP) && player_yFactor1 > 0) {
		player_yFactor1 *= 0.5f;
	}

	int newY = player_pos.y + (int)player_yFactor1;

	if (player_canMove(player_pos.x, newY)) {
		if (player_pos.y > newY) {
			player_jumping = 1;
		}
		if (!player_jumping) {
			player_falling = 1;
		}
		player_pos.y = newY;
	}
	else {
		player_yFactor1 = 0;
		player_jumping = 0;
		player_falling = 0;
	}
}

int player_animState() {
	return player_anim;
}

void player_init() {
	player_pos = wpos(w_start.x * 40, w_start.y * 40);
}

void player_attack() {
	if (player_attacking > 0) return;
	player_attacking = 1;
	// enemy scan

}
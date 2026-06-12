#include "cplworld.h"
#include "ginput.h"
#include <math.h>
#define M_RAD (3.14159F / 180.0f)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern void gameovergui_init();
extern wchunk_t* w_chunks;
extern size_t w_chunksSize;
extern pos_t w_start;
extern CTICK w_upticks;
extern float saved_x;
extern float saved_y;
extern char has_save;
pos_t player_pos;
float player_yFactor1;
CTICK player_yFactor2;
int player_anim;
int player_hp = 100;
;
char player_direction = 0; 
char player_walk = 0;
char player_attacking = 0;
char player_jumping = 0;

CTICK _viewUpLast = 0;
CTICK _viewUpLastSub = 0;

void player_updateView() {
	if (_viewUpLast < cplTicks()) {
		_viewUpLast = cplTicks() + 1;
		//
		if (!caworld_onground() && player_attacking == 0) {
			if (player_jumping) {
				if (player_anim < 40) player_anim = 39;
				player_anim++;
				if (player_anim > 46) player_anim = 41;
			}
			else {
				if (player_anim < 30) player_anim = 30;
				player_anim++;
				if (player_anim > 33) player_anim = 31;
			}
		}
		else {
			if (player_anim > 29 && player_anim < 50) player_anim = 1;
		}
		if (player_walk && caworld_onground()) {
			player_walk = 0;
			if (player_anim < 10) player_anim = 10;
			else 
				player_anim++;
			if (player_anim > 20) player_anim = 11;
		}
		else {
			if (player_anim > 9 && player_anim < 21) player_anim = 1;
		}
		if (player_anim < 9) {
			player_anim++;
			if (player_anim > 8) player_anim = 1;
		}
	}
	if (_viewUpLastSub < w_upticks) {
		_viewUpLastSub = w_upticks + 6;
		//
		if (player_anim == 25 && player_attacking == 0) {
			player_anim = 1;
		}
		if (player_attacking > 0) {
			if (caworld_onground()) {
				if (player_anim < 20) player_anim = 20;
				player_anim++;
				if (player_anim > 24) {
					player_attacking = 0;
					player_anim = 1;
				}
			} 
			else {
				if (player_anim < 50) {
					player_anim = 50;
				}
				else
					player_anim++;
				if (player_anim > 53) {
					player_attacking = 0;
				}
			}
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
		player_jumping = player_pos.y < newY;

		player_pos.y = newY;
	}
	else {
		if (player_jumping) {
			player_yFactor2 = cplTicks() + 5;
		}
		player_yFactor1 = 0;
		player_jumping = 0;
	}
	if (player_hp <= 0) {
		gameovergui_init();
	}


	CTICK spike_cd = 0;

	for (int i = 0; i < w_chunksSize; i++) {

		const edict_t* ed = ewgetEdict(i);
		if (!ed) continue;

		for (int j = 0; j < 64; j++) {

			edict_t e = ed[j];

			if (e.type == 110) { 

				int ex = i * 40;
				int ey = j * 40;

				if (abs(player_pos.x - ex) < 20 &&
					abs(player_pos.y - ey) < 20 &&
					spike_cd < cplTicks()) {

					player_hp -= 10;
					spike_cd = cplTicks() + 30;
				}
			}
		}
	}
}

int player_animState() {
	return player_anim;
}



void player_init() {
	if (has_save) {
		player_pos = wpos(saved_x, saved_y);
	}
	else {
		player_pos = wpos(w_start.x * 40, w_start.y * 40);
	}
}

void player_attack() {
	if (player_attacking > 0) return;
	player_attacking = 1;
	// enemy scan

}
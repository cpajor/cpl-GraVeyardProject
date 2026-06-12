#ifndef CPLWORLD_H
#define CPLWORLD_H
#include "cpl.h"

edict_t* ewgetEdict(int pos);

void caworld_load(char* wname);

int caworld_getType(int x, int y);

void caworld_setCollide(int x, int y, char collide);

void caworld_tick();

void caworld_camera(pos_t pos);

// player

#ifndef CPL_EDITOR

void player_init();

char player_checkTile(int type);

char player_canMove(int x, int y); 

void player_updateView();

int player_animState();

char caworld_onground();

void player_attack();
extern int player_hp;
void gameovergui_init();
#endif // !CPL_EDITPR
#endif
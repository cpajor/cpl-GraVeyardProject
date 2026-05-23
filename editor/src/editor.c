#include "cplvid.h"
#include "cplthread.h"

extern int c_state;
extern void _mem_init(); // mem.c
extern void _rnd_init(); // glwnd.c
extern void _rnd_thread(); // glwnd.c

extern void cplthr_init(); // cpl_thread.cpp

CTICK _game_uptime = 0;

CTICK cplTicks() {
	return _game_uptime;
}

void _editor_thread(int id) {
	DWORD nextTick = GetTickCount64();
	while (c_state) {
		DWORD now = GetTickCount64();
		while (now >= nextTick) {
			//game_tick();

			_game_uptime++;
			nextTick += 100;
		}
	}
}

void keyboard_key(int key, char state) {

}

void edit_start() {
	_mem_init();
	cplthr_init();
	_rnd_init();

	cplthr_set(0, _editor_thread);
	_rnd_thread();
}

int main(int argc, char** argv) {
	edit_start();
}
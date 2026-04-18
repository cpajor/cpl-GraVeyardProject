#include "cplthread.h"

#include <thread>

typedef struct csound_t;

std::thread __thr[CPL_MAX_THREADS];
thr_func_t _thr_funcs[CPL_MAX_THREADS];
char _thr_state = 1;

void _thr_idle(int id) {
	while (_thr_state) {
		if (_thr_funcs[id] != 0) {
			_thr_funcs[id]();
		}
	}
}

void cplthr_exit() {
	_thr_state = 0;
	for (int i = 0; i < CPL_MAX_THREADS; i++) {
		_thr_funcs[i] = 0;
	}
}

extern "C" 
void cplthr_init() {
	for (int i = 0; i < CPL_MAX_THREADS; i++) {
		_thr_funcs[i] = 0;
		//
		__thr[i] = std::thread(_thr_idle, i);
		__thr[i].detach();
	}
	std::atexit(cplthr_exit);
}

void cplthr_set(char id, thr_func_t func) {
	if (CPL_MAX_THREADS <= id) return;
	//
	_thr_funcs[id] = func;
}
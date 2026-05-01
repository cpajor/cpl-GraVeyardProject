#include "cplthread.h"

#include <thread>

thr_func_t _thr_funcs[CPL_MAX_THREADS];
char _thr_state = 1;

void _thr_idle(int id) {
	while (_thr_state) {
		if (_thr_funcs[id] != 0) {
			_thr_funcs[id](id);
		}
	}
}

void cplthr_exit() {
	_thr_state = 0;
	for (int i = 0; i < CPL_MAX_THREADS; i++) {
		_thr_funcs[i] = 0;
	}
}

void _thr_temp_idle(voidfunc_t func, params_t par) {
	if (_thr_state) {
		func(par);
	}
}

extern "C" 
void cplthr_init() {
	for (int i = 0; i < CPL_MAX_THREADS; i++) {
		_thr_funcs[i] = 0;
		//
		std::thread(_thr_idle, i).detach();
	}
	std::atexit(cplthr_exit);
}

void cplthr_set(char id, thr_func_t func) {
	if (CPL_MAX_THREADS <= id) return;
	//
	_thr_funcs[id] = func;
}

void cplasync(voidfunc_t t, params_t par) {
	std::thread(_thr_temp_idle, t, par).detach();
}
#include "cplthread.h"
#include <stdlib.h>
#include <stdio.h>

extern void _rnd_init(); // glrender.c
extern void _rnd_thread(); // glrender.c

void StartEditor() {
	_rnd_init();
	//

	//
	_rnd_thread();
}
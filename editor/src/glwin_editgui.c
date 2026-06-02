#include "cplvid.h"
#include "editor.h"
#include <stdlib.h> 
#include <stdio.h>

extern int w_currX;
extern int w_currY;
extern char w_mode;
extern wchunk_t* w_chunks;
extern int w_chunksSize;

char _choosed_gui = 0;

void cpl_drawEditGuis() {
	if (_choosed_gui == 2) {
		for (int i = 0x100; i < 0x11A; i++) {
			
		}
	}
}

void applyBrush() {
	int type = memgeti("e_brushtype");
	if (w_currY < 0 || w_currY >= 64 || w_currX < 0 || w_currX > w_chunksSize - 1) return;
	if (w_mode) {
		w_chunks[w_currX].edicts[w_currY].typeBack = type;
	}
	else {
		w_chunks[w_currX].edicts[w_currY].type = type;
	}
}
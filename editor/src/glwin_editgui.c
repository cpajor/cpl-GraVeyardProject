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
	char sz = memgeti("e_brushsize");
	int type = memgeti("e_brushtype");
	for (int i = w_currX - sz; i < w_currX + sz; i++) {
		for (int j = w_currX - sz; j < w_currX + sz; j++) {
			if (i >= 0 && i < w_chunksSize && j >= 0 && j < 64) {
				if (w_mode) {
					w_chunks[i].edicts[j].typeBack = type;
				}
				else {
					w_chunks[i].edicts[j].type = type;
				}
			}
		}
	}
}
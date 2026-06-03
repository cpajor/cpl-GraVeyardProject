#include "cplworld.h"
#include <math.h>
#define M_RAD (3.14159F / 180.0f)

extern wchunk_t* w_chunks;
extern size_t w_chunksSize;

pos_t p_pos;

char _viewUpLast = 0;

void player_calcCollide() {
	for (int i = 0; i < w_chunksSize; i++) {
		for (int j = 0; j < 64; j++) {
			w_chunks[i].edicts[j].collide = 0;
		}
	}
	//
	for (int a = 0; a < 360; a += 15) {
		float rad = a * M_RAD;

		float dx = cosf(rad);
		float dy = sinf(rad);

		pos_t hit = wcpy(p_pos);

		while (1) {
			hit.x += dx * 4.0f;
			hit.y += dy * 4.0f;

			int tx = (int)(hit.x / 40);
			int ty = (int)(hit.y / 40);

			if (tx < 0 || ty < 0 || tx >= w_chunksSize || ty >= 64) break;

			if (w_chunks[tx].edicts[ty].type > 0) {
				w_chunks[tx].edicts[ty].collide = 1;
				break;
			}
		}
	}
}

void player_tick() {
	
}


void player_updateView() {
	if (_viewUpLast + 2 < cplTicks()) {
		_viewUpLast = cplTicks();
		player_calcCollide();
	}
	//

}
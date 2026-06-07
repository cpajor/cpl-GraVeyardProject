#include "editor.h"
#include "cplworld.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern wchunk_t* w_chunks;
extern size_t w_chunksSize;
extern int w_palette;
extern pos_t w_start;

void cworld_save() {
	char* wname = memgetc("e_wname");
	if (wname == 0 || strlen(wname) < 5) {
		printf("ERR eworldfile.c / worldname is null\n");
		return;
	}
	FILE* fp = fopen(wname, "wb");
	if (!fp) {
		printf("ERR eworldfile.c / fopen\n");
		return;
	}

	wheader_t header = { 0, w_chunksSize, w_palette, w_start };

	fwrite(&header, sizeof(wheader_t), 1, fp);
	fwrite(w_chunks, sizeof(wchunk_t), w_chunksSize, fp);

	printf("INFO file saved.\n");

	fclose(fp);
}
	
void cworld_load() {
	char* wname = memgetc("e_wname");
	if (wname == 0 || strlen(wname) < 5) {
		printf("ERR eworldfile.c / worldname is null\n");
		return;
	}
	FILE* fp = fopen(wname, "rb");
	if (!fp) {
		printf("ERR eworldfile.c / fopen\n");
		return;
	}
	
	wheader_t header;
	fread(&header, sizeof(wheader_t), 1, fp);

	w_chunksSize = header.edictsize;
	w_palette = header.palette;
	w_start = header.start;

	w_chunks = malloc(sizeof(wchunk_t) * w_chunksSize);

	fread(w_chunks, sizeof(wchunk_t), w_chunksSize, fp);

	fclose(fp);

	printf("INFO loaded %lli chunks\n", w_chunksSize);

}

void cworld_new() {
	w_chunksSize = memgeti("e_wsize");
	w_chunks = malloc(sizeof(wchunk_t) * w_chunksSize);
	w_palette = memgeti("e_wpalette");
	w_start = wpos(1, 1);

	for (int i = 0; i < w_chunksSize; i++) {
		w_chunks[i].pos = wpos(i, 0);
		for (int j = 0; j < 64; j++) {
			w_chunks[i].edicts[j].type = 100;
			w_chunks[i].edicts[j].collide = 1;
			w_chunks[i].edicts[j].typeBack = 100;
		}
	}

	w_chunks[1].edicts[1].type = 101;

}
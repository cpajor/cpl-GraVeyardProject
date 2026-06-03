#include "cplworld.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern wchunk_t* w_chunks;
extern int w_chunksSize;

void cworld_load(char* wname) {
	FILE* fp = fopen(wname, "rb");
	if (!fp) {
		printf("ERR eworldfile.c / fopen\n");
		return;
	}

	wheader_t header;
	fread(&header, sizeof(wheader_t), 1, fp);

	w_chunksSize = header.edictsize;

	w_chunks = malloc(sizeof(wchunk_t) * w_chunksSize);

	fread(w_chunks, sizeof(wchunk_t), w_chunksSize, fp);

	fclose(fp);
}
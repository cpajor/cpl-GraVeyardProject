#include "editor.h"
#include "cpl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern wchunk_t* w_chunks;
extern int w_chunksSize;

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

	wheader_t header = { 0, w_chunksSize };

	fwrite(&header, sizeof(wheader_t), 1, fp);
	fwrite(&w_chunks, sizeof(wchunk_t), w_chunksSize, fp);

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

	w_chunks = malloc(sizeof(wchunk_t) * header.edictsize);

	fread(&w_chunks, sizeof(wchunk_t), header.edictsize, fp);

	w_chunksSize = header.edictsize;

	printf("INFO loaded %i chunks\n", w_chunksSize);

	fclose(fp);
}

void cworld_new() {
	w_chunksSize = memgeti("e_wsize");
	w_chunks = malloc(sizeof(wchunk_t) * w_chunksSize);

	for (int i = 0; i < w_chunksSize; i++) {

	}

}
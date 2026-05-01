#include "cpl.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct mem_s {
	char name[32];
	int valueI;
	char* valueC;
	//csound_t* valueS;
	unsigned int valueT;
} mem_t;

mem_t* _cpl_memory;

char* y1cbuf;
int y1csiz;

void cmemset(char name[32]) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strcmp("_", m->name)) {
			strcpy(m->name, name);
			return;
		}
	}
}

void memseti(char name[32], int in) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strncmp(m->name, name, strlen(m->name))) {
			m->valueI = in;
			return;
		}
	}
	cmemset(name);
	memseti(name, in);
}

void memsetc(char name[32], char* in) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strncmp(m->name, name, strlen(m->name))) {
			m->valueC = in;
			return;
		}
	}
	cmemset(name);
	memsetc(name, in);
}

/*
void memsets(char name[32], csound_t* in) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strncmp(m->name, name, strlen(m->name))) {
			m->valueS = in;
			return;
		}
	}
	cmemset(name);
	memsets(name, in);
}
*/

void memsett(char name[32], unsigned int in) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strncmp(m->name, name, strlen(m->name))) {
			m->valueT = in;
			return;
		}
	}
	cmemset(name);
	memsett(name, in);
}

int memgeti(char name[32]) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strncmp(m->name, name, strlen(m->name))) {
			return m->valueI;
		}
	}
	return 0;
}

char* memgetc(char name[32]) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strncmp(m->name, name, strlen(m->name))) {
			return m->valueC;
		}
	}
	return 0;
}

/*
csound_t* memgets(char name[32]) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strncmp(m->name, name, strlen(m->name))) {
			return m->valueS;
		}
	}
	return 0;
}
*/

unsigned int memgett(char name[32]) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strncmp(m->name, name, strlen(m->name))) {
			return m->valueT;
		}
	}
	return 0;
}

int memgetii(CPLMEM id) {
	if (id > _CPL_MEMORY_MAX) return 0;
	return _cpl_memory[id].valueI;
}

char* memgetic(CPLMEM id) {
	if (id > _CPL_MEMORY_MAX) return 0;
	return _cpl_memory[id].valueC;
}

/*
csound_t* memgetis(CPLMEM id) {
	if (id > _CPL_MEMORY_MAX) return 0;
	return _cpl_memory[id].valueS;
}
*/

unsigned int memgetit(CPLMEM id) {
	if (id > _CPL_MEMORY_MAX) return 0;
	return _cpl_memory[id].valueT;
}

CPLMEM memgetId(char name[32]) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strncmp(m->name, name, strlen(m->name))) {
			return (CPLMEM) i;
		}
	}
	return _CPL_MEMORY_MAX + 1;
}

void cmemtest() {
	memsetc("memtests", "cos");
	memgetc("memtests");
}

void _mem_init() {
	_cpl_memory = malloc((sizeof(mem_t) * _CPL_MEMORY_MAX));
	_cpl_memory[0] = (mem_t){ "version", 1, 0, 0  };
	_cpl_memory[1] = (mem_t){ "name", 0, "cp-L", 0};
	for (int i = 2; i < _CPL_MEMORY_MAX; i++) {
		_cpl_memory[i] = (mem_t){ "_", 0, 0, 0 };
	}
	cmemtest();
	//
}

params_t params_empty() {
	// fixed
	params_t par;
	par.size = 0;

	return par;
}

char cgetBit(char in, char pos) {
	return (in >> pos) & 1;
}

char csetBit(char in, char pos, char v) {
	if (v)
		return in | (1 << pos);   
	else
		return in & ~(1 << pos); 
}

void* y1get(const char* y1file, const char* internalFile, int* out_filesize) {
	/*
		to improve - 'goto' is outdated (if works - do NOT touch it)
	*/
	y1header_t header;
	y1file_t yfile;

	FILE* fp = fopen(y1file, "rb");
	if (!fp) return 0;

	if (!fread(&header, sizeof(header), 1, fp))
		goto y1ret;
	if (memcmp(header.id, "CPL2", 4) != 0)
		goto y1ret;

	int num_files = header.size / sizeof(y1file_t);

	if (fseek(fp, header.offset, SEEK_SET) != 0)
		goto y1ret;

	for (int i = 0; i < num_files; i++) {
		if (!fread(&yfile, sizeof(y1file_t), 1, fp))
			goto y1ret;

		if (!strcmp(yfile.name, internalFile)) {

			if (fseek(fp, yfile.offset, SEEK_SET) != 0)
				goto y1ret;

			void* buffer = malloc(yfile.size);
			if (!buffer)
				goto y1ret;

			if (!fread(buffer, yfile.size, 1, fp)) {
				free(buffer);
				goto y1ret;
			}

			if (out_filesize)
				*out_filesize = yfile.size;

			fclose(fp);
			return buffer;
		}
	}

y1ret:
	fclose(fp);
	return 0;
}

void y1zero() {
	free(y1cbuf);
	y1cbuf = 0;
	y1csiz = 0;
}

char* y1load(const char* inter) {
	y1zero();
	y1cbuf = y1get(REZFILE, inter, &y1csiz);
	return y1cbuf;
}
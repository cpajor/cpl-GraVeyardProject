/*
 * cpL-Tec series 1 implementation
 * github.com/cpajor
 * 
 */
#include "cpl.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct mem_s {
	char name[32];
	int valueI;
	char* valueC;
	unsigned int valueT;
} mem_t;

mem_t* _cpl_memory;
char* y1cbuf;
int y1csiz;

int cmemset(char name[32]) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strcmp("_", m->name)) {
			strcpy(m->name, name);
			return i;
		}
	}
	return 0;
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

char* memgetci(CPLMEM id) {
	if (id > _CPL_MEMORY_MAX) return 0;
	return _cpl_memory[id].valueC;
}

unsigned int memgetti(CPLMEM id) {
	if (id > _CPL_MEMORY_MAX) return 0;
	return _cpl_memory[id].valueT;
}

void memsetti(CPLMEM id, unsigned int in) {
	if (id > _CPL_MEMORY_MAX || id == 0) return 0;
	_cpl_memory[id].valueT = in;
}

void memsetii(CPLMEM id, int in) {
	if (id > _CPL_MEMORY_MAX || id == 0) return 0;
	_cpl_memory[id].valueI = in;
}

void memsetci(CPLMEM id, char* in) {
	if (id > _CPL_MEMORY_MAX || id == 0) return 0;
	_cpl_memory[id].valueC = in;
}

CPLMEM memget(char name[32]) {
	for (int i = 0; i < _CPL_MEMORY_MAX; i++) {
		mem_t* m = &_cpl_memory[i];
		if (!strncmp(m->name, name, strlen(m->name))) {
			return (CPLMEM) i;
		}
	}
	return 0;
}

void _mem_init() {
	//
	_cpl_memory = malloc((sizeof(mem_t) * _CPL_MEMORY_MAX));
	_cpl_memory[0] = (mem_t){ "version", 1, 0, 0  };
	_cpl_memory[1] = (mem_t){ "name", 0, "cp-L", 0};
	for (int i = 2; i < _CPL_MEMORY_MAX; i++) {
		_cpl_memory[i] = (mem_t) { "_", 0, 0, 0 };
	}
	//

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

void* y1get(const char* internalFile, int* out_filesize) {
	// to improve - 'goto' is outdated (but if works - do NOT touch it)
	y1header_t header;
	y1file_t yfile;

	FILE* fp = fopen(REZFILE, "rb");
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
	y1csiz = 0;
}

char* y1load(const char* inter) {
	y1zero();
	y1cbuf = y1get(inter, &y1csiz);
	return y1cbuf;
}

pos_t wpos(int x, int y) {
	return (pos_t) { x, y };
}

pos_t wcpy(pos_t pos) {
	return (pos_t) { pos.x, pos.y };
}

char wposcmp(pos_t b1, pos_t b2) {
	return b1.x == b2.x && b1.y == b2.y;
}

char strnstartswith(const char* str, const char* prefix, int n) {
	for (int i = 0; i < n; i++) {
		if (str[i] != prefix[i]) return 1;
	}
	return 0;
}

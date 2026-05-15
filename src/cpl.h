#define _CRT_SECURE_NO_WARNINGS
#ifndef CPL_H
#define CPL_H
#define _CPL_MEMORY_MAX 512

#define CPLMEM unsigned short
#define CTICK unsigned __int64

#define REZFILE "REZ.Y1"

typedef struct y1header_s {
	char id[4];
	int offset;
	int size;
} y1header_t;

typedef struct y1file_s {
	char name[56];
	int offset;
	int size;
} y1file_t;

typedef struct location_s {
	double x;
	double y;
	// extra
	double rot;
} location_t;

typedef struct pos_s {
	int x;
	int y;
} pos_t;

typedef struct edict_s {
	int type;
	char collide;
	pos_t pos;
} edict_t;

typedef struct wheader_s {
	char version;
	int seed;
	int edictsize;
} wheader_t;

typedef struct wchunk_s {
	int seed;
	int edictsize;

	edict_t* edicts;
} wchunk_t;

typedef struct params_s {
	CPLMEM* params;
	unsigned char size;
} params_t;

typedef void (*voidfunc_t)(params_t params);
typedef void (*cplgui_init_f)();
typedef void (*cplgui_input_f)(char key[11]);
typedef void (*cplgui_idle_f)();

#ifndef tex_t
#define tex_t unsigned int
#endif 

//fix
typedef unsigned __int64 size_t;

// mem.c
CPLMEM memget(char name[32]);
//
int memgetii(CPLMEM id);
char* memgetci(CPLMEM id);
unsigned int memgetti(CPLMEM id);
//
void memsetti(CPLMEM id, unsigned int in);
void memsetii(CPLMEM id, int in);
void memsetci(CPLMEM id, char* in);
//
void memseti(char name[32], int in);
void memsetc(char name[32], char* in);
void memsett(char name[32], unsigned int in);
//
int memgeti(char name[32]);
char* memgetc(char name[32]);
unsigned int memgett(char name[32]);

params_t params_empty();

char cgetBit(char in, char pos);
char csetBit(char in, char pos, char v);

void* y1get(const char* internalFile, int* out_filesize);
char* y1load(const char* inter);
void y1zero();

//
CTICK cplTicks();

#endif
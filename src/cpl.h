#define _CRT_SECURE_NO_WARNINGS
#ifndef CPL_H
#define CPL_H
/*	
 *  MSVC ONLY (GCC, CLANG, etc. won't work)
 * 
 *  SAME AS C++ TRY/CATCH 
 * 
 *	EXAMPLE USE
 *	
 *	CTRY {
 *		not 100% sure code
 *	} CCATCH {
 *		in exception handling etc.
 *	}
 * 
 */ 
#define CTRY __try
#define CCATCH __except (1)
//
#define _CPL_MEMORY_MAX 512
#define CPLMEM unsigned short
#define CTICK unsigned __int64

#define REZFILE "REZ.Y1"

#define CW_VERSION 3
#define CW_MAXCHUNKS 2048

// fix
typedef unsigned __int64 size_t;

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

typedef struct pos_s {
	int x;
	int y;
} pos_t;

typedef struct edict_s {
	int type;
	int typeBack;
	char collide;
} edict_t;

typedef struct wchunk_s {
	pos_t pos;
	edict_t edicts[64];
} wchunk_t;

typedef struct wheader_s {
	char version;
	size_t edictsize;
	int palette;
	pos_t start;
} wheader_t;

typedef struct params_s {
	CPLMEM* params;
	unsigned char size;
} params_t;

typedef void (*voidfunc_t)(params_t* params);
typedef void (*cplgui_init_f)();
typedef void (*cplgui_input_f)(char key[11]);
typedef void (*cplgui_idle_f)();

#ifndef tex_t
#define tex_t unsigned int
#endif 

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

char cgetBit(char in, char pos);
char csetBit(char in, char pos, char v);

void* y1get(const char* internalFile, int* out_filesize);
char* y1load(const char* inter);
void y1zero();

pos_t wpos(int x, int y);

pos_t wcpy(pos_t pos);

char wposcmp(pos_t b1, pos_t b2);


char strnstartswith(const char* str, const char* prefix, int n);

//
CTICK cplTicks();

#endif
#define _CRT_SECURE_NO_WARNINGS
#ifndef CPL_H
#define CPL_H
#define _CPL_MEMORY_MAX 512

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

typedef struct csound_s {
    int samples;
    int sampleRate;
    short* data;
} csound_t;

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

typedef struct winfo_s {
	int startx;
	int starty;

} winfo_t;

typedef struct wheader_s {
	char version;

	int edictsize;
} wheader_t;

typedef struct wscene_s {
	winfo_t info;

	edict_t* edicts;
} wscene_t;

typedef struct wfile_s {
	wheader_t header;
	int scenesize;
	wscene_t* scenes;
} wfile_t;

typedef void (*voidfunc_t)();
typedef void (*cplgui_init_f)();
typedef void (*cplgui_input_f)(char key[11]);
typedef void (*cplgui_idle_f)();

#ifndef tex_t
#define tex_t unsigned int
#endif 

// mem.c

void memseti(char name[32], int in);
void memsetc(char name[32], char* in);
void memsets(char name[32], csound_t* in);
void memsett(char name[32], unsigned int in);
int memgeti(char name[32]);
char* memgetc(char name[32]);
csound_t* memgets(char name[32]);
unsigned int memgett(char name[32]);

char cgetBit(char in, char pos);
char csetBit(char in, char pos, char v);

void* y1get(const char* y1file, const char* internalFile, int* out_filesize);

void y1load(const char* inter);

void y1zero();

#endif
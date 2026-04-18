#include "cpl.h"
#include "cplvid.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/***********************************
  *								   *
  * CIG - Cpajor ImaGe File Format *
  * VERSION : 0.2				   *
  *								   *
  ***********************************/
#define CIG_VERSION 2
//
#define uchar unsigned char
#define ushort unsigned short

typedef struct cigheader_s {
	char version;
	short width;
	short height;
	unsigned int size;
} cigheader_t;

typedef struct cigfile_s {
	cigheader_t header;
	ushort* data;
} cigfile_t;

typedef cigfile_t cig_t;

//

extern char* y1cbuf; // mem.c
extern int y1csiz; // mem.c

extern int txGen(unsigned char* buf, int width, int height); // glwnd.c

uchar* cigToImg(cigfile_t in, int* lenght) {
	uchar* ret = malloc(sizeof(uchar) * ((size_t)in.header.size * 4));
	
	int k = 0;
	for (int j = 0; j < in.header.size; j++) {

		ushort ca = in.data[j];

		// A RRRRR GGGGG BBBBB
		ret[k + 3] = ((ca >> 15) & 1) > 0 ? 255 : 0;

		ret[k/**/] = (((ca >> 10) & 0b11111) * 8);
		ret[k + 1] = (((ca >> 5) & 0b11111) * 8);
		ret[k + 2] = (((ca >> 0) & 0b11111) * 8);
		//

		k += 4;
	}

	*lenght = k;
	return ret;
}

tex_t y1txCIG() {
	cigfile_t fil;

	const uchar* pointer = (const uchar*)y1cbuf;

	memcpy(&fil.header, pointer, sizeof(cigheader_t));
	pointer += sizeof(cigheader_t);

	fil.data = malloc(sizeof(ushort) * fil.header.size);

	memcpy(fil.data, pointer, sizeof(ushort) * fil.header.size);

	int ic = 0;
	uchar* img = cigToImg(fil, &ic);

	return txGen(img, fil.header.width, fil.header.height);
}
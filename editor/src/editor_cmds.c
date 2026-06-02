#include "editor.h"
#include "cplworld.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern pos_t w_curr;
extern pos_t w_cur2;

void cmd_callCmd(char* str) {
	if (!strcmp(str, "EXIT")) {
		exit(0);
		return;
	}
	if (!strnstartswith(str, "NAME ", 5)) {
		int len = strlen(str) - 5;
		if (len < 3) {
			printf("ERR editor_cmds.c / worldname is too short!\n");
			return; 
		}
		char* buf = malloc(len);
		memcpy(buf, str + 5, len);
		memsetc("e_wname", buf);
		printf("INFO e_wname set to: %s\n", memgetc("e_wname"));
		return;
	}
	if (!strnstartswith(str, "WSIZE ", 6)) {
		int len = strlen(str) - 6;
		if (len < 1) {
			return;
		}
		int c = 0;
		CTRY {
			c = atoi(str + 6);
		}
		CCATCH {}
		if (c > CW_MAXCHUNKS || c < 20) {
			printf("ERR editor_cmds.c / worldsize is wrong (20 - %i)\n", CW_MAXCHUNKS);
			return;
		}
		memseti("e_wsize", c);
		printf("INFO e_wsize set to: %i\n", memgeti("e_wsize"));
		return;
	}
	if (!strnstartswith(str, "B ", 2)) {
		int len = strlen(str) - 2;
		if (len < 1) {
			return;
		}
		int c = 0;
		CTRY {
			c = atoi(str + 2);
		}
		CCATCH {
			c = 0;
		}
		if (c < 0x100 || c > 0xFFF) {
			printf("ERR editor_cmds.c / brushtype is wrong (255 - 4095)\n");
			return;
		}
		memseti("e_brushtype", c);
		printf("INFO brushtype set to: %i\n", memgeti("e_brushtype"));
		return;
	}
	if (!strnstartswith(str, "BRUSHTYPE ", 10)) {
		int len = strlen(str) - 10;
		if (len < 1) {
			return;
		}
		int c = 0;
		CTRY {
			c = atoi(str + 10);
		}
		CCATCH {
			c = 0;
		}
		if (c < 0x100 || c > 0xFFF) {
			printf("ERR editor_cmds.c / brushtype is wrong (255 - 4095)\n");
			return;
		}
		memseti("e_brushtype", c);
		printf("INFO brushtype set to: %i\n", memgeti("e_brushtype"));
		return;
	}
	if (!strcmp(str, "NEW")) {
		cworld_new();
		printf("INFO cworld new\n");
	}
	if (!strcmp(str, "LOAD")) {
		cworld_load();
		printf("INFO cworld loaded\n");
	}
	if (!strcmp(str, "SAVE")) {
		cworld_save();
		printf("INFO cworld saved\n");
	}
}
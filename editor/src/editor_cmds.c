#include "editor.h"
#include "cplworld.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void cmd_callCmd(char* str) {
	if (!strcmp(str, "EXIT")) {
		exit(0);
		return;
	}
	if (!strnstartswith(str, "NAME ", 5)) {
		int len = strlen(str) - 4;
		if (len < 5) {
			return; 
		}
		char* buf = (char*)malloc(len - 4);
		memcpy(buf, str + 5, len - 4);
		memsetc("e_wname", buf);
		printf("INFO e_wname set to: %s\n", memgetc("e_wname"));
		return;
	}
	if (!strnstartswith(str, "WSIZE ", 6)) {
		int len = strlen(str) - 6;
		if (len < 1) {
			return;
		}
		int c = 1;
		CTRY {
			c = atoi(str + 6);
		} 
		CCATCH {
			printf("ERR editor_cmds.c / worldsize is wrong (1 - 64)\n");
			return;
		}
		if (c > 64) {
			printf("ERR editor_cmds.c / worldsize is wrong (1 - 64)\n");
			return;
		}
		memseti("e_wsize", c);
		printf("INFO e_wsize set to: %i\n", memgeti("e_wsize"));
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
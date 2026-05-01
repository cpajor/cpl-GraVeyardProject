#include "cplrez.h"
#include "cplaudio.h"
#include "cplvid.h"

extern char* y1cbuf;

void rezLoadReg() {
	//
	y1load("level/menu/back1.cig");
	memsett(TEX_MENU_0, y1txCIG());
}
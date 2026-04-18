#include "cplrez.h"
#include "cplaudio.h"
#include "cplvid.h"

void rezLoadReg() {
	y1load("sound/menu/CLICK.WAV");
	memsets(SND_CLICK, csnd_Y1());
	y1load("sound/menu/TITLE.WAV");
	memsets(SND_TITLE, csnd_Y1());
	//
	y1load("level/menu/back1.cig");
	memsett(TEX_MENU_0, y1txCIG());
}
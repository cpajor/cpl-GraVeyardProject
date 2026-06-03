#include "cplrez.h"
#include "cplaudio.h"
#include "cplvid.h"

extern CPLMEM cclaw_tex[];

void rezLoadReg() {
	//
	y1load("entity/coin.cig");
	memsett("spec_coin", y1txCIG());
	y1load(TEX_LEVEL1_0);
	memsett("level1_0", y1txCIG());
	//
	y1load("entity/claw/idle.cig");
	memsett("claw_0", y1txCIG());
	cclaw_tex[0] = memget("claw_0");

	y1load("entity/claw/run.cig");
	memsett("claw_1", y1txCIG());
	cclaw_tex[1] = memget("claw_1");


}
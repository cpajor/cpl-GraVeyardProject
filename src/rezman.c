#include "cplrez.h"
#include "cplaudio.h"
#include "cplvid.h"

extern tex_t cclaw_tex[];

void rezLoadReg() {
	//
	y1load("entity/coin.cig");
	memsett("spec_coin", y1txCIG());

	y1load("entity/fire.cig");
	memsett("spec_fire", y1txCIG());

	y1load(TEX_LEVEL1_0);
	memsett("level1_0", y1txCIG());
	//
	y1load("entity/claw/idle.cig");
	cclaw_tex[0] = y1txCIG();

	y1load("entity/claw/run.cig");
	cclaw_tex[1] = y1txCIG();

	y1load("entity/claw/attack1.cig");
	cclaw_tex[2] = y1txCIG();

	y1load("entity/claw/fall.cig");
	cclaw_tex[3] = y1txCIG();

	y1load("entity/claw/jump.cig");
	cclaw_tex[4] = y1txCIG();

	y1load("entity/claw/attackj.cig");
	cclaw_tex[5] = y1txCIG();
}
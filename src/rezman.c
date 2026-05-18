#include "cplrez.h"
#include "cplaudio.h"
#include "cplvid.h"

void rezLoadReg() {
	//
	y1load("misc/coin.cig");
	memsett("spec_coin", y1txCIG());
}
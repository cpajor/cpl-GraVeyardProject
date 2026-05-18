#include "cplvid.h"
#include <windows.h>
#include <stdlib.h> 
#include <stdio.h>

void cpl_drawSpecial(char type, int x, int y) {
	if (type == CPLSPEC_COIN) {
		cpl_rTexQuadOff(memgett("spec_coin"), x, y, 32, 32, 1, (cplTicks() % 9) * 0.1, 1, 0.1);
	}
}
#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"
#include "ginput.h"

#include <stdio.h>
#include <string.h>



void optionsgui_key(char key[11]) {
	if (key[CKEY_ESC]) {

	}
}

void optionsgui_draw() {
	
}

void optionsgui_init() {
	cplgui_setIdle(optionsgui_draw);
	cplgui_setInput(optionsgui_key);

}
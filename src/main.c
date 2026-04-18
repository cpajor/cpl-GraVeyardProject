extern void StartGame(); // game.c

extern void StartEditor(); // TODO

extern void _mem_init(); // mem.c
extern void win32c_init(); // win32.c

extern void cplthr_init(); // cpl_thread.cpp

int main(int argc, char* argv[]) {
	_mem_init();
	win32c_init();
	cplthr_init();
	//StartEditor();
	StartGame();
	/*
	if (argc == 1) {
		StartGame();
	}
	else {

	}
	*/
	return 0;
}
#include "cplthread.h"

#include <iostream>
#include <string>

void ecmd_pullCmd() {
	std::cout << "> ";
	std::string str;
	std::cin >> str;
	//
	if (!str.compare("exit")) {
		exit(0);
	}

}

extern "C" {
	
	void _editorcmds_thread(int id) {
		while (cplState()) {
			ecmd_pullCmd();
		}
	}
}
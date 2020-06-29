//
// Created by walaryne on 6/29/20.
//

#include "OFSFacade.h"
#include "../gui/OFSGui.h"

void testFunc() {
	std::cout << "The button is pressed" << std::endl;
}

void *CreateInterface(char const *name, int *err) {
	OFSGui g;

	g.bindActivity(BUT_CLICKED_UPDATE, testFunc);
	while(g.loop()) {
	}
	std::cout << "LOL IT WORKS FAM" << std::endl;
	return nullptr;
}
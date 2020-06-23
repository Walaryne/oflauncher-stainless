#include "OFSLayout.h"

DEFINE_LAYOUT(setupLayout) { // main menu
	clearLayout();
	// Keep in mind, the order they are added to the vector are the order they
	// are rendered to the screen.

	// Background image
	addImage("../res/bg.bmp");

	addButton("../res/update.bmp", BUT_CLICKED_UPDATE, 100, 100, 2);

	addImage("../res/tab.bmp", 0, 0, 1);
	setLastIndex(1);
	addButton("../res/tab.bmp", TAB_CLICKED_OPTIONS, 64, 0, 1);

	bindActivity(TAB_CLICKED_OPTIONS,
				 OFSGui::setupLayoutOptions); // not implemented
											  // yet
}

DEFINE_LAYOUT(setupLayoutOptions) {
	clearLayout();

	// Background image
	addImage("../res/bg.bmp");

	addButton("../res/tab.bmp", TAB_CLICKED_MAIN, 0, 0, 1);

	addImage("../res/tab.bmp", 64, 0, 1);
	setLastIndex(1);

	bindActivity(TAB_CLICKED_MAIN, OFSGui::setupLayout);
}
#include "OFSLayout.h"

#include "res/bg.bmp.h"
#include "res/install.bmp.h"
#include "res/spinny.bmp.h"
#include "res/cancel.bmp.h"

DEFINE_LAYOUT(preInstallLayout) {
	clearLayout();

	// Background image
	addImage((const void*)bg_bmp, bg_bmp_len);

	addButton((const void*)install_bmp, install_bmp_len, BUT_CLICKED_INSTALL, -1, 100, 2);

	bindActivity(BUT_CLICKED_INSTALL, OFSGui::installLayout);
}
DEFINE_LAYOUT(installLayout) {
	clearLayout();

	// Background image
	addImage((const void*)bg_bmp, bg_bmp_len);

	addText("Installing", 70, -1, 100);

	addSpinny(spinny_bmp, spinny_bmp_len, -1, 200);

	addButton(cancel_bmp, cancel_bmp_len, BUT_CLICKED_CANCEL, -1, 310, 2);

	bindActivity(BUT_CLICKED_CANCEL, OFSGui::preInstallLayout);
}

// OLD LAYOUT, DELETE LATER
/*
DEFINE_LAYOUT(setupLayout) { // main menu
	clearLayout();
	// Keep in mind, the order they are added to the vector are the order they
	// are rendered to the screen.

	// Background image
	addImage("../res/bg.bmp");

	addText("Installing", 70, 180, 100);
	//addButton("../res/update.bmp", BUT_CLICKED_UPDATE, 100, 100, 2);

	//addImage("../res/tab.bmp", 0, 0, 1);
	setLastIndex(1);
	//addButton("../res/tab.bmp", TAB_CLICKED_OPTIONS, 64, 0, 1);

	addSpinny("../res/spinny.bmp", 288, 200);

	//bindActivity(TAB_CLICKED_OPTIONS,
	//			 OFSGui::setupLayoutOptions); // not implemented
											  // yet
}

DEFINE_LAYOUT(setupLayoutOptions) {
	clearLayout();

	// Background image
	addImage("../res/bg.bmp");

	addButton("../res/tab.bmp", TAB_CLICKED_MAIN, 0, 0, 1);

	addImage("../res/tab.bmp", 64, 0, 1);
	setLastIndex(1);

	addText("Test Option", 5, 80);
	addTextEntry("Text here", 200, 80, 300);

	bindActivity(TAB_CLICKED_MAIN, OFSGui::setupLayout);
} */

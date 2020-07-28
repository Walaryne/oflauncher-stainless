#include "OFSLayout.h"

#ifdef INCLUDE_RESOURCES
#include "res/bg.bmp.h"
#include "res/cancel.bmp.h"
#include "res/install.bmp.h"
//#include "res/spinny.bmp.h"
#include "res/barM.bmp.h"
#include "res/SourceSansPro-Regular.ttf.h"
#endif

DEFINE_LAYOUT(preInstallLayout) {
	clearLayout();

	// Background image
	addImage(DATA(bg));

	addButton(FONTDATA(SourceSansPro_Regular), BUT_CLICKED_INSTALL, "Install", -1, 100, BIG_BOY_BUTTON);

	bindActivity(BUT_CLICKED_INSTALL, OFSGui::installLayout);
}
DEFINE_LAYOUT(installLayout) {
	clearLayout();

	// Background image
	addImage(DATA(bg));

	addText(FONTDATA(SourceSansPro_Regular),"Installing", 70, -1, 100);

	// addSpinny(DATA(spinny), -1, 200);
	addProgressBar(DATA(barM), -1, 250, 300);

	addButton(FONTDATA(SourceSansPro_Regular), BUT_CLICKED_CANCEL, "Cancel", -1, 290, SMALL_BUTTON);

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

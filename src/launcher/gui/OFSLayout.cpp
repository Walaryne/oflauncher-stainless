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
	addImage("background", DATA(bg));

	addButton("install", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_INSTALL, "Install", -1, 100, BIG_BOY_BUTTON);

	addButton("options", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_OPTIONS, "Options", 50, 200, SMALL_BUTTON);

	bindActivity(BUT_CLICKED_INSTALL, OFSGui::installLayout);
	bindActivity(BUT_CLICKED_OPTIONS, OFSGui::SteamDirOption);
}
DEFINE_LAYOUT(installLayout) {
	clearLayout();

	// Background image
	addImage("background", DATA(bg));

	addText("install button", FONTDATA(SourceSansPro_Regular),"Installing", 70, -1, 100);

	// addSpinny(DATA(spinny), -1, 200);
	addProgressBar("progress", DATA(barM), -1, 250, 300);

	addButton("cancel", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_CANCEL, "Cancel", -1, 290, SMALL_BUTTON);

	bindActivity(BUT_CLICKED_CANCEL, OFSGui::preInstallLayout);

}
DEFINE_LAYOUT(SteamDirOption) {
	clearLayout();

	addImage("background", DATA(bg));

	addText("message", FONTDATA(SourceSansPro_Regular), "Please enter the directory you have steam installed in.", 28, -1, 200);
	addTextEntry("steamPath", FONTDATA(SourceSansPro_Regular), "Edit me", 100, 300, 400);

	addButton("accept", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_MAIN, "Accept", 50, 450, SMALL_BUTTON);

	bindActivity(BUT_CLICKED_MAIN, OFSGui::preInstallLayout);
}
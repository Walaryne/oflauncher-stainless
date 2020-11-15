#include "OFSLayout.h"

#ifdef INCLUDE_RESOURCES
#include "res/bg.bmp.h"
#include "res/cancel.bmp.h"
#include "res/install.bmp.h"
//#include "res/spinny.bmp.h"
#include "res/barM.bmp.h"
#include "res/folder.bmp.h"
#include "res/gear2.bmp.h"
#include "res/SourceSansPro-Regular.ttf.h"
#include "res/tf2build.ttf.h"
#endif

DEFINE_LAYOUT(preInstallLayout) {
	clearLayout();

	// Background image
	addImage("background", DATA(bg));

	addButton("install button", FONTDATA(tf2build), BUT_CLICKED_INSTALL, "Install", -1, 100, BIG_BOY_BUTTON);

	//addButton("options", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_OPTIONS, "Options", 50, 200, SMALL_BUTTON);
	addImgButton("options", DATA(gear2), BUT_CLICKED_OPTIONS, 810, 400, SMALL_BUTTON);

	bindActivity(BUT_CLICKED_INSTALL, OFSGui::installLayout);
	bindActivity(BUT_CLICKED_OPTIONS, OFSGui::SteamDirOption);
}
DEFINE_LAYOUT(installLayout) {
	clearLayout();

	// Background image
	addImage("background", DATA(bg));

	addText("install", FONTDATA(tf2build),"Installing", 70, -1, 100);

	// addSpinny(DATA(spinny), -1, 200);
	addProgressBar("progress", DATA(barM), INSTALL_FINISHED, -1, 250, 300);

	addButton("cancel", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_CANCEL, "Cancel", -1, 290, SMALL_BUTTON);

	bindActivity(BUT_CLICKED_CANCEL, OFSGui::preInstallLayout);
	bindActivity(INSTALL_FINISHED, OFSGui::postInstall);

}
DEFINE_LAYOUT(SteamDirOption) {
	clearLayout();

	addImage("background", DATA(bg));

	addText("message", FONTDATA(tf2build), "Options", 42, -1, 100);
	addText("message", FONTDATA(SourceSansPro_Regular), "Steam Directory:", 25, 100, 200);
	addTextEntry("steamPath", FONTDATA(SourceSansPro_Regular), "Edit me", 100, 240, 400);
	addButton("redogaminfo", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_UPDATEGAMEINFO, "Regenerate gameinfo.txt", 100, 310, SMALL_BUTTON);
	addButton("verify", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_VERIFYINTEGRITY, "Verify integrity of game files", 400, 310, SMALL_BUTTON);

	addButton("back", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_MAIN, "Back", 50, 450, SMALL_BUTTON);
	addButton("saveop", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_SAVEOP, "Save Settings", 150, 450, SMALL_BUTTON);

	addDirButton("dirChooser", DATA(folder), BUT_CLICKED_UPDATE_DIR, 520, 220, SMALL_BUTTON);

	bindActivity(BUT_CLICKED_MAIN, OFSGui::preInstallLayout);
}
DEFINE_LAYOUT(postInstall) {
	clearLayout();
	addImage("background", DATA(bg));
	addText("message", FONTDATA(tf2build), "Install Complete!", 50, -1, 100);
	addText("message", FONTDATA(SourceSansPro_Regular), "Please restart steam to see the game in your library.", 25, -1, 150);
	addButton("launchGame", FONTDATA(tf2build), BUT_CLICKED_LAUNCH, "Launch", -1, 190, BIG_BOY_BUTTON);
}
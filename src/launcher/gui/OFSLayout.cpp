#include "OFSLayout.h"

#ifdef INCLUDE_RESOURCES
#include "res/bg.bmp.h"
#include "res/cancel.bmp.h"
#include "res/install.bmp.h"
#include "res/spinny.bmp.h"
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

	addSpinny("loadingSpinny", DATA(spinny), -1, 200);
	addProgressBar("progress", DATA(barM), INSTALL_FINISHED, -1, 300, 300);

	addButton("cancel", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_CANCEL, "Cancel", -1, 340, SMALL_BUTTON);

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
	bindActivity(BUT_CLICKED_VERIFYINTEGRITY, OFSGui::verifyFiles);
	//bindActivity(BUT_CLICKED_MAIN, OFSGui::selectUser);
}
DEFINE_LAYOUT(postInstall) {
	clearLayout();
	addImage("background", DATA(bg));
	addText("message", FONTDATA(tf2build), "Install Complete!", 50, -1, 100);
	addText("message", FONTDATA(SourceSansPro_Regular), "Please restart steam to see the game in your library.", 25, -1, 150);
	addButton("launchGame", FONTDATA(tf2build), BUT_CLICKED_LAUNCH, "Close", -1, 190, BIG_BOY_BUTTON);
	bindActivity(BUT_CLICKED_LAUNCH, OFSGui::quitLayout);

	bindActivity(BUT_CLICKED_SHOW_STEAMUSER, OFSGui::selectUser);
}

DEFINE_LAYOUT(selectUser) {
	clearLayout();
	addImage("background", DATA(bg));
	addText("title", FONTDATA(tf2build), "Select user to install for", 40, -1, 40);
	addButtonArray(FONTDATA(SourceSansPro_Regular), BUT_CLICKED_STEAMUSER, -1, 100, SMALL_BUTTON);

	bindActivity(BUT_CLICKED_STEAMUSER, OFSGui::postInstall);
}

DEFINE_LAYOUT(verifyFiles) {
	clearLayout();

	// Background image
	addImage("background", DATA(bg));

	addText("vf", FONTDATA(tf2build),"Verifying Integrity of game Files", 50, -1, 100);

	addSpinny("loadingSpinny", DATA(spinny), -1, 200);

	//addButton("cancel", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_CANCEL, "Cancel", -1, 340, SMALL_BUTTON);

	bindActivity(BUT_CLICKED_OPTIONS, OFSGui::postVerifyFiles);
	//bindActivity(VERIFY_FINISHED, OFSGui::SteamDirOption);

}

DEFINE_LAYOUT(postVerifyFiles) {
	clearLayout();

	// Background image
	addImage("background", DATA(bg));

	if(!verified) {
		addText("vf", FONTDATA(tf2build),"Verification Finished.", 50, -1, 100);
		addText("vf", FONTDATA(tf2build),"No errors detected.", 30, -1, 160);
	}
	else {
		addText("vf", FONTDATA(tf2build),
				"Verification Finished.",
				50, -1, 100);
		addText("vf", FONTDATA(tf2build),
				std::to_string(verified) +
					" file(s) need to be redownloaded.",
				30, -1, 160);
		addText("vf", FONTDATA(tf2build),
				"Update to fetch them.",
				30, -1, 190);
	}

	addButton("cancel", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_OPTIONS, "Back to Options", -1, 340, SMALL_BUTTON);

	bindActivity(BUT_CLICKED_OPTIONS, OFSGui::SteamDirOption);
}

DEFINE_LAYOUT(quitLayout) {
	quit();
}
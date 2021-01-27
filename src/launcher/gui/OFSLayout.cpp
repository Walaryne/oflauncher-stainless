#include "OFSLayout.h"


#include "res/bg.bmp.h"
#include "res/stripe.bmp.h"
#include "res/cancel.bmp.h"
#include "res/install.bmp.h"
#include "res/spinny.bmp.h"
#include "res/barM.bmp.h"
#include "res/promo.bmp.h"
#include "res/dir.bmp.h"
#include "res/dir_sel.bmp.h"
#include "res/gear2.bmp.h"
#include "res/SourceSansPro-Regular.ttf.h"
#include "res/tf2build.ttf.h"
#include "res/SourceCodePro-Bold.ttf.h"
#include "res/SourceCodePro-Regular.ttf.h"


DEFINE_LAYOUT(preInstallLayout) {
	clearLayout();

	// Background image
	addImage("background", DATA(bg));
	addText("upName", FONTDATA(SourceCodePro_Bold), "NEW UPDATE AVAILABLE!", 30, 570, 60);
	addImage("promo", DATA(promo), 570, 100);
	addButton("patch notes", FONTDATA(SourceCodePro_Bold), BUT_CLICKED_PN, "PATCH NOTES", 570, 300, 25);

	addButton("install button", FONTDATA(SourceCodePro_Bold), BUT_CLICKED_INSTALL, "INSTALL", 30, 100, 25);
	addButton("options", FONTDATA(SourceCodePro_Bold), BUT_CLICKED_OPTIONS, "OPTIONS", 30, 130, 25);

	//addButton("options", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_OPTIONS, "Options", 50, 200, SMALL_BUTTON);
	//addImgButton("options", DATA(gear2), BUT_CLICKED_OPTIONS, 810, 400, SMALL_BUTTON);
	addImage("stripe", DATA(stripe), 0, 470);
	addText("log", FONTDATA(SourceCodePro_Bold), "industries.TF", 25, 730, 490);

	bindActivity(BUT_CLICKED_INSTALL, OFSGui::installLayout);
	bindActivity(BUT_CLICKED_OPTIONS, OFSGui::SteamDirOption);
}
DEFINE_LAYOUT(installLayout) {
	clearLayout();

	// Background image
	addImage("background", DATA(bg));

	addText("install", FONTDATA(SourceCodePro_Bold),"INSTALLING...", 25, 30, 100);

	addSpinny("loadingSpinny", DATA(spinny), -1, 200);
	addProgressBar("progress", DATA(barM), INSTALL_FINISHED, -1, 300, 300);

	addButton("cancel", FONTDATA(SourceCodePro_Bold), BUT_CLICKED_CANCEL, "CANCEL", 30, 490, 25);

	addImage("stripe", DATA(stripe), 0, 470);
	addText("log", FONTDATA(SourceCodePro_Bold), "industries.TF", 25, 730, 490);

	bindActivity(BUT_CLICKED_CANCEL, OFSGui::preInstallLayout);
	bindActivity(INSTALL_FINISHED, OFSGui::postInstall);

}
DEFINE_LAYOUT(SteamDirOption) {
	clearLayout();

	addImage("background", DATA(bg));

	addText("message", FONTDATA(SourceCodePro_Bold), "OPTIONS", 25, 30, 100);
	addText("message", FONTDATA(SourceCodePro_Bold), "STEAM DIRECTORY:", 25, 30, 200);
	addTextEntry("steamPath", FONTDATA(SourceCodePro_Regular), "Edit me", 280, 200, 400);
	addButton("redogaminfo", FONTDATA(SourceCodePro_Bold), BUT_CLICKED_UPDATEGAMEINFO, "REGENERATE GAMEINFO.TXT", 30, 230, 25);
	addButton("verify", FONTDATA(SourceCodePro_Bold), BUT_CLICKED_VERIFYINTEGRITY, "VERIFY INTEGRITY OF GAME FILES", 30, 260, 25);

	addButton("back", FONTDATA(SourceCodePro_Bold), BUT_CLICKED_MAIN, "BACK", 30, 490, 25);
	addButton("saveop", FONTDATA(SourceCodePro_Bold), BUT_CLICKED_SAVEOP, "SAVE SETTINGS", 30, 320, 25);

	addDirButton("dirChooser", DATA(dir), DATA(dir_sel),BUT_CLICKED_UPDATE_DIR, 685, 203, SMALL_BUTTON);

	addImage("stripe", DATA(stripe), 0, 470);
	addText("log", FONTDATA(SourceCodePro_Bold), "industries.TF", 25, 730, 490);

	bindActivity(BUT_CLICKED_MAIN, OFSGui::preInstallLayout);
	bindActivity(BUT_CLICKED_VERIFYINTEGRITY, OFSGui::verifyFiles);
	//bindActivity(BUT_CLICKED_MAIN, OFSGui::selectUser);
}
DEFINE_LAYOUT(postInstall) {
	clearLayout();
	addImage("background", DATA(bg));
	addText("message", FONTDATA(SourceCodePro_Bold), "INSTALL COMPLETE!", 25, 30, 100);
	addText("message", FONTDATA(SourceCodePro_Bold), "PLEASE RESTART STEAM TO SEE IT IN YOUR LIBRARY.", 25, 30, 130);
	addButton("launchGame", FONTDATA(SourceCodePro_Bold), BUT_CLICKED_LAUNCH, "CLOSE", 30, 190, 25);

	addImage("stripe", DATA(stripe), 0, 470);
	addText("log", FONTDATA(SourceCodePro_Bold), "industries.TF", 25, 730, 490);

	bindActivity(BUT_CLICKED_LAUNCH, OFSGui::quitLayout);

	bindActivity(BUT_CLICKED_SHOW_STEAMUSER, OFSGui::selectUser);
}

DEFINE_LAYOUT(selectUser) {
	clearLayout();
	addImage("background", DATA(bg));
	addText("title", FONTDATA(tf2build), "SELECT USER TO INSTALL FOR", 40, -1, 40);
	addButtonArray(FONTDATA(SourceCodePro_Bold), BUT_CLICKED_STEAMUSER, -1, 100, 25);

	addImage("stripe", DATA(stripe), 0, 470);
	addText("log", FONTDATA(SourceCodePro_Bold), "industries.TF", 25, 730, 490);

	bindActivity(BUT_CLICKED_STEAMUSER, OFSGui::postInstall);
}

DEFINE_LAYOUT(verifyFiles) {
	clearLayout();

	// Background image
	addImage("background", DATA(bg));

	addText("vf", FONTDATA(SourceCodePro_Bold),"VERIFYING INTEGRITY OF GAME FILES...", 25, 30, 100);

	addSpinny("loadingSpinny", DATA(spinny), -1, 200);

	addImage("stripe", DATA(stripe), 0, 470);
	addText("log", FONTDATA(SourceCodePro_Bold), "industries.TF", 25, 730, 490);

	//addButton("cancel", FONTDATA(SourceSansPro_Regular), BUT_CLICKED_CANCEL, "Cancel", -1, 340, SMALL_BUTTON);

	bindActivity(BUT_CLICKED_OPTIONS, OFSGui::postVerifyFiles);
	//bindActivity(VERIFY_FINISHED, OFSGui::SteamDirOption);

}

DEFINE_LAYOUT(postVerifyFiles) {
	clearLayout();

	// Background image
	addImage("background", DATA(bg));

	if(!verified) {
		addText("vf", FONTDATA(SourceCodePro_Bold),"VERIFICATION FINISHES.", 25, 30, 100);
		addText("vf", FONTDATA(SourceCodePro_Bold),"NO ERRORS DETECTED.", 25, 30, 130);
	}
	else {
		addText("vf", FONTDATA(SourceCodePro_Bold),
				"VERIFICATION FINISHED.",
				25, 30, 100);
		addText("vf", FONTDATA(SourceCodePro_Bold),
				std::to_string(verified) +
					" FILES(S) NEED TO BE REDOWNLOADED",
				25, 30, 130);
		addText("vf", FONTDATA(SourceCodePro_Bold),
				"UPDATE TO FETCH THEM.",
				25, 30, 160);
	}

	addButton("cancel", FONTDATA(SourceCodePro_Bold), BUT_CLICKED_OPTIONS, "BACK TO OPTIONS", 30, 490, 25);

	addImage("stripe", DATA(stripe), 0, 470);
	addText("log", FONTDATA(SourceCodePro_Bold), "industries.TF", 25, 730, 490);

	bindActivity(BUT_CLICKED_OPTIONS, OFSGui::SteamDirOption);
}

DEFINE_LAYOUT(quitLayout) {
	quit();
}
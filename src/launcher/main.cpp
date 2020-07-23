#include "main.h"


void checkDirsExist() {
	fs::path remote = fs::path("launcher/remote").make_preferred();
	fs::path local = fs::path("launcher/local").make_preferred();

	if(!fs::exists(remote)) {
		fs::create_directories(remote);
	}
	if(!fs::exists(local)) {
		fs::create_directories(local);
	}
}

void updateFunc() {
	//db->updateGame();
}

int main(int argc, char *argv[]) {
	bool runFromGame = false;
	for(int i = 0; i < argc; i++)
		if(strcmp(argv[i], "-check-for-updates") == 0)
			runFromGame = true;

	// Initialize cURL for usage program wide
	curl_global_init(CURL_GLOBAL_ALL);

	OFSGui g;
	OFSPathDiscover opd;

	//g.bindActivity(BUT_CLICKED_INSTALL, testFunc);

	if(runFromGame)
		g.simulateButton(BUT_CLICKED_INSTALL);

	std::string gameFolderName = "open_fortress";

	try {
		fs::path of = fs::path(opd.getSourcemodsPath() + "/" + gameFolderName).make_preferred();

		if(!fs::exists(of)) {
			fs::create_directories(of);
		}

		fs::current_path(of);

		checkDirsExist();

		OFSNet net("http://svn.openfortress.fun/files", gameFolderName);

		// To Fenteale: This should be called the moment that the "Update"
		// button is pressed.
		net.fetchDatabase();

		OFSDatabase db(&net);

		db.updateGame();

		//g.bindActivity(BUT_CLICKED_INSTALL, updateFunc);
	} catch(std::exception &e) {
		if(!runFromGame) {
			std::string error_msg =
				"Cannot connect to Update Server. Please check internet.\n";
			error_msg.append(e.what());
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cannot Connect",
									 error_msg.c_str(), nullptr);
		}
	}

	// To Fenteale: Later on you'll have direct access to two automated
	// functions. These will be updateGame and verifyIntegrity respectively.
	// I'll try to add some callbacks and stuff so you can use progress bars!

	// gui is setup.  run all installer stuff

	while(g.loop()) {
		g.setProgress(0.5f);
	}
	return 0;
}

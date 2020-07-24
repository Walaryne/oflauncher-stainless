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
	// db->updateGame();
}

int main(int argc, char *argv[]) {
	bool runFromGame = false;
	for(int i = 0; i < argc; i++)
		if(strcmp(argv[i], "-check-for-updates") == 0)
			runFromGame = true;

	// Initialize cURL for usage program wide
	curl_global_init(CURL_GLOBAL_ALL);

	OFSGui g;
	g.loop(); // run once to just have it display correctly while init
			  // everything else
	OFSPathDiscover opd;

	// g.bindActivity(BUT_CLICKED_INSTALL, testFunc);

	if(runFromGame)
		g.simulateButton(BUT_CLICKED_INSTALL);

	std::string gameFolderName = "open_fortress";

	TRYCATCHERR_START()
	fs::path of = fs::path(opd.getSourcemodsPath() + "/" + gameFolderName)
					  .make_preferred();

	if(!fs::exists(of)) {
		fs::create_directories(of);
	}

	fs::current_path(of);

	checkDirsExist();
	TRYCATCHERR_END("Could not find or set directory correctly.")

	OFSNet net("http://svn.openfortress.fun/files", gameFolderName);

	// To Fenteale: This should be called the moment that the "Update"
	// button is pressed.
	net.fetchDatabase();

	OFSDatabase db(&net);

	// To Fenteale: Later on you'll have direct access to two automated
	// functions. These will be updateGame and verifyIntegrity respectively.
	// I'll try to add some callbacks and stuff so you can use progress bars!

	// gui is setup.  run all installer stuff

	while(g.loop()) {
		if(g.ifActivity(BUT_CLICKED_INSTALL)) {
			TRYCATCHERR_START()
			db.updateGame();
			TRYCATCHERR_END("Failed to update game")
		}

		g.setProgress(0.5f);
	}
	return 0;
}

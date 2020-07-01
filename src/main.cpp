#include "main.h"

void checkDirsExist() {
	fs::path gameDir = fs::path("open_fortress");
	fs::path remote = fs::path("open_fortress/launcher/remote").make_preferred();
	fs::path local = fs::path("open_fortress/launcher/local").make_preferred();
	if(!fs::exists(gameDir)) {
		fs::create_directory(gameDir);
	}
	if(!fs::exists(remote)) {
		fs::create_directory(remote);
	}
	if(!fs::exists(local)) {
		fs::create_directory(local);
	}
}

void testFunc() {
	std::cout << "The button is pressed" << std::endl;
}

int main(int argc, char *argv[]) {
	bool runFromGame = false;
	for(int i = 0; i < argc; i++)
		if(strcmp(argv[i], "-check-for-updates") == 0)
			runFromGame = true;

	// Initialize cURL for usage program wide
	curl_global_init(CURL_GLOBAL_ALL);

	OFSPathDiscover opd;

	chdir(opd.getSourcemodsPath().c_str());

	checkDirsExist();

	try {
		OFSNet net("http://127.0.0.1", "open_fortress");

		// To Fenteale: This should be called the moment that the "Update"
		// button is pressed.
		net.fetchDatabase();

		OFSDatabase db(&net);

		db.updateGame();
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

	OFSGui g;
	g.bindActivity(BUT_CLICKED_INSTALL, testFunc);

	if(runFromGame)
		g.simulateButton(BUT_CLICKED_INSTALL);
	while(g.loop()) {
	}
}

#include "main.h"

void checkDirsExist() {
	if(!fs::exists("remote")) {
		fs::create_directory("remote");
	}
	if(!fs::exists("local")) {
		fs::create_directory("local");
	}
	if(!fs::exists("open_fortress")) {
		fs::create_directory("open_fortress");
	}
}

void testFunc() {
	std::cout << "The button is pressed" << std::endl;
}

int main() {

	// Initialize cURL for usage program wide
	curl_global_init(CURL_GLOBAL_ALL);

	checkDirsExist();

	try {
		OFSNet net("http://127.0.0.1", "open_fortress");

		// To Fenteale: This should be called the moment that the "Update"
		// button is pressed.
		net.fetchDatabase();

		OFSDatabase db(&net);

		db.updateGame();
	} catch(std::exception &e) {
		std::string error_msg =
			"Cannot connect to Update Server. Please check internet.\n";
		error_msg.append(e.what());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cannot Connect",
								 error_msg.c_str(), nullptr);
	}

	// To Fenteale: Later on you'll have direct access to two automated
	// functions. These will be updateGame and verifyIntegrity respectively.
	// I'll try to add some callbacks and stuff so you can use progress bars!

	OFSGui g;

	g.bindActivity(BUT_CLICKED_UPDATE, testFunc);
	while(g.loop()) {
	}
}

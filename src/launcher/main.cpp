#include "main.h"

// threading stuff
SDL_sem *butDataLock = nullptr;
SDL_sem *progDataLock = nullptr;
SDL_sem *continueDataLock = nullptr;
int butStateData = 0;
float progData = 0;
bool continueData = true;

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

int doGui(void *ptr) {
	TRYCATCHERR_START()
	OFSGui g;
	while(g.loop()) {
		GuiActs a = g.getLastAct();
		if(a) {
			SDL_SemWait(progDataLock);
			g.setProgress(progData);
			std::cout << "Current pog: " << progData << std::endl;
			 SDL_SemPost(progDataLock);
			SDL_SemWait(butDataLock);
			butStateData = a;
			SDL_SemPost(butDataLock);

		}
	}
	TRYCATCHERR_END("OFSGui")
	SDL_SemWait(continueDataLock);
	continueData = false;
	SDL_SemPost(continueDataLock);
	return 0;
}

int main(int argc, char *argv[]) {
	bool runFromGame = false;
	for(int i = 0; i < argc; i++)
		if(strcmp(argv[i], "-check-for-updates") == 0)
			runFromGame = true;

	// Initialize cURL for usage program wide
	curl_global_init(CURL_GLOBAL_ALL);

	// init semaphore for checking button data
	butDataLock = SDL_CreateSemaphore(1);
	progDataLock = SDL_CreateSemaphore(1);

	SDL_Thread *guiThread = SDL_CreateThread(doGui, "Gui", (void *)nullptr);

	OFSPathDiscover opd;

	// if(runFromGame)
	// g.simulateButton(BUT_CLICKED_INSTALL);

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
	bool c = true;
	while(c) {
		SDL_SemWait(butDataLock);
		int FiredGuiAct = butStateData;
		butStateData = NOT_CLICKED;
		SDL_SemPost(butDataLock);
		if(FiredGuiAct) {
			if(FiredGuiAct == BUT_CLICKED_INSTALL) {
				TRYCATCHERR_START()
				db.compareRevisions();
				int totalFiles = db.getQueueSize();
				while(!db.downloadSingleFile() && c)
				{
					SDL_SemWait(progDataLock);
					progData = (float)db.getQueueSize() / (float)totalFiles;
					SDL_SemPost(progDataLock);
					SDL_SemWait(continueDataLock);
					c = continueData;
					SDL_SemPost(continueDataLock);
				}
				if(c)
					db.copyDb();

				//db.updateGame();
				TRYCATCHERR_END("Failed to update game")
			}
		}
		SDL_SemWait(continueDataLock);
		c = continueData;
		SDL_SemPost(continueDataLock);
		SDL_Delay(100);
	}
	SDL_WaitThread(guiThread, nullptr);
	SDL_DestroySemaphore(butDataLock);
	SDL_DestroySemaphore(progDataLock);
	return 0;
}

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
	std::string autoDetectSteamPath = *((std::string *)ptr);
	OFSGui g;
	float prog;
	while(g.loop()) {
		//set progress
		SDL_SemWait(progDataLock);
		prog = progData;
		SDL_SemPost(progDataLock);

		g.sendEvent("progress", EVENT_PROGBAR_UPDATE, &prog);

		GuiActs a = g.getLastAct();
		if(a) {
			void * data;
			switch(a) {
			case BUT_CLICKED_UPDATE_DIR:
				data = g.getData("dirChooser", DATA_DIR);
				if(data != nullptr)
					g.sendEvent("steamPath", EVENT_DATA_TEXT_UPDATE, data);
				break;
			case BUT_CLICKED_OPTIONS:
				g.sendEvent("steamPath", EVENT_DATA_TEXT_UPDATE, &autoDetectSteamPath);
				//no break here, we actually want it to also perform the default action
			default:
				SDL_SemWait(butDataLock);
				butStateData = a;
				SDL_SemPost(butDataLock);
				break;
			}
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
	butDataLock = SDL_CreateSemaphore(2);
	progDataLock = SDL_CreateSemaphore(2);
	continueDataLock = SDL_CreateSemaphore( 2);

	//This string should be set to the steam path that will be displayed in the
	//options menu!  We gotta make a specific function to get this path to set
	//it here.
	std::string steamPath = "/home/fenteale/.steam";

	SDL_Thread *guiThread = SDL_CreateThread(doGui, "Gui", (void *)(&steamPath));

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
			switch(FiredGuiAct) {
			case BUT_CLICKED_INSTALL:
				TRYCATCHERR_START()
				db.compareRevisions();
				int totalFiles = db.getQueueSize();
				while(!db.downloadSingleFile() && c && (FiredGuiAct != BUT_CLICKED_CANCEL))
				{
					SDL_SemWait(progDataLock);
					progData = ((float)totalFiles - (float)db.getQueueSize()) / (float)totalFiles;
					SDL_SemPost(progDataLock);
					SDL_SemWait(continueDataLock);
					c = continueData;
					SDL_SemPost(continueDataLock);
					SDL_SemWait(butDataLock);
					FiredGuiAct = butStateData;
					butStateData = NOT_CLICKED;
					SDL_SemPost(butDataLock);
				}
				if(c && (FiredGuiAct != BUT_CLICKED_CANCEL)) {
					db.copyDb();
                    SDL_SemWait(progDataLock);
                    progData = 1.0f;
                    SDL_SemPost(progDataLock);
				}

				TRYCATCHERR_END("Failed to update game")
				break;
			case BUT_CLICKED_LAUNCH:
				openURL("steam://run/243750");
				break;
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

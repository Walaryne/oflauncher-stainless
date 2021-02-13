#include "main.h"

// threading stuff
SDL_sem *butDataLock = nullptr;
SDL_sem *progDataLock = nullptr;
SDL_sem *continueDataLock = nullptr;
SDL_sem *verifyStateLock = nullptr;
int butStateData = 0;
float progData = 0;
bool continueData = true;
bool firstTime = false;
int verifyState = -2;


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
	verifyStateLock = SDL_CreateSemaphore(2);

	//This string should be set to the steam path that will be displayed in the
	//options menu!  We gotta make a specific function to get this path to set
	//it here.
	std::string steamPath;



	//OFSPathDiscover opd;
	OFSSteam* steam = nullptr;
	OFSConfig cf;
	TRYCATCHERR_START()
	cf.loadFromDisk();
	if(!cf.exists("/steamPath"))	{
		firstTime=true;
		steam = new OFSSteam();
		steamPath = steam->getSteamPath().string();
		cf.writeValue("/steamPath", steamPath);
		cf.commitToDisk();
	}
	else {
		cf.readValue("/steamPath", steamPath);
		steam = new OFSSteam(steamPath);
	}

	TRYCATCHERR_END("Can't load config file.")

	TRYCATCHERR_START()
	if(!steam->getApp(440))
	{
		SDL_MessageBoxButtonData buttons[] = {
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Yes"},
			{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "No"}
		};

		SDL_MessageBoxData askTF2 = {
			SDL_MESSAGEBOX_WARNING,
			nullptr,
			"Did not detect TF2",
			"Team Fortress 2 must be installed before you are\n"
			"able to run Open Fortress.\n\n"
			"Install now?",
			SDL_arraysize(buttons),
			buttons,
			nullptr
		};
		int buttonid;
		if(SDL_ShowMessageBox(&askTF2, &buttonid) < 0)
			throw;
		if(buttonid == 0)
			openURL("steam://install/440");
	}
	if(!steam->getApp(243750))
	{
		SDL_MessageBoxButtonData buttons[] = {
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Yes"},
			{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "No"}
		};

		SDL_MessageBoxData askSDK = {
			SDL_MESSAGEBOX_WARNING,
			nullptr,
			"Did not detect Source SDK Base",
			"Source SDK Base 2013 Multiplayer must be\n"
			"installed before you are able to run Open Fortress.\n\n"
			"Install now?",
			SDL_arraysize(buttons),
			buttons,
			nullptr
		};
		int buttonid;
		if(SDL_ShowMessageBox(&askSDK, &buttonid) < 0)
			throw;
		if(buttonid == 0)
			openURL("steam://install/243750");
	}

	TRYCATCHERR_END("Couldn't display prompt messages.")





	SDL_Thread *guiThread = SDL_CreateThread(doGui, "Gui", (void *)(&steamPath));

	// if(runFromGame)
	// g.simulateButton(BUT_CLICKED_INSTALL);

	std::string gameFolderName = "open_fortress";


	TRYCATCHERR_START()
	fs::path of = fs::path(steam->getSourcemodsPath() / gameFolderName)
					  .make_preferred();

	if(firstTime)
	{
		OFSImportSVN svn(of);
		std::cout << "Is this an SVN import? " << svn.isSVN() << std::endl;
	}

	//std::cout << steam.getApp(440)->getName() << std::endl;
	//std::cout << steam.getApp(440)->getInstallPath() << std::endl;

	if(!fs::exists(of)) {
		fs::create_directories(of);
	}



	fs::current_path(of);

	checkDirsExist();
	TRYCATCHERR_END("Could not find or set directory correctly.")

	OFSNet net("http://svn.openfortress.fun/zstd", gameFolderName);
	//OFSNet net("http://127.0.0.1/", gameFolderName);

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
				while(!db.downloadFiles(progData, &butStateData) && c && (FiredGuiAct != BUT_CLICKED_CANCEL))
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
				if(c && (butStateData != BUT_CLICKED_CANCEL)) {
					db.copyDb();
                    SDL_SemWait(progDataLock);
                    progData = 1.0f;
                    SDL_SemPost(progDataLock);
					if(firstTime)
					{
						writeGameInfo(fs::current_path(), steam);
#ifdef __LINUX__
						//put code to write launch options here
#endif
					}
				}

				TRYCATCHERR_END("Failed to update game")
				break;
			case BUT_CLICKED_LAUNCH:
				openURL("steam://run/243750");
				break;
			case BUT_CLICKED_PN:
				openURL("https://openfortress.fun");
				break;
			case BUT_CLICKED_UPDATEGAMEINFO:
				writeGameInfo(fs::current_path(), steam);
				break;
			case BUT_CLICKED_VERIFYINTEGRITY:
				SDL_SemWait(verifyStateLock);
				verifyState = -1;
				SDL_SemPost(verifyStateLock);
				std::cout << "Verifying integrity..." << std::endl;
				int vi = db.compareIntegrity();
				std::cout << vi << std::endl;
				SDL_SemWait(verifyStateLock);
				verifyState = vi;
				SDL_SemPost(verifyStateLock);
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

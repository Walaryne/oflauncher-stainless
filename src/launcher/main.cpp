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

#ifdef WIN32
#ifdef SHOW_CMD_ON_WINDOWS
int main(int argc, char *argv[]) {
#else
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	int argc = 1;
	char *argv[1];
	argv[0] = lpCmdLine;
#endif
#else
int main(int argc, char *argv[]) {
#endif
	bool runFromGame = false;
	bool isInGameFolder = false;
	for(int i = 0; i < argc; i++) {
		if(strcmp(argv[i], "-check-for-updates") == 0)
			runFromGame = true;
		if(strcmp(argv[i], "-force-run") == 0)
			isInGameFolder = true;
	}

	fs::path launcherCheck = fs::current_path();
	launcherCheck = launcherCheck / ".." / ".." / "open_fortress" / "launcher" / EXENAME;
	std::cout << "Checking path: " << launcherCheck.string() << std::endl;
	if(fs::exists(launcherCheck ))
		isInGameFolder = true;

	// Initialize cURL for usage program wide
	

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
		if(OFSYesNoDialog("Did not detect TF2", "Team Fortress 2 must be installed before you are\n"
												"able to run Open Fortress.\n\n"
												"Install now?") == 0)
			openURL("steam://install/440");
	}
	if(!steam->getApp(243750))
	{
		if(OFSYesNoDialog("Did not detect Source SDK Base", "Source SDK Base 2013 Multiplayer must be\n"
															"installed before you are able to run Open Fortress.\n\n"
															"Install now?") == 0)
			openURL("steam://install/243750");
	}

	TRYCATCHERR_END("Couldn't display prompt messages.")

	std::string gameFolderName = "open_fortress";
	fs::path of = fs::path(steam->getSourcemodsPath() / gameFolderName)
		.make_preferred();
	fs::path launcherPath = of / "launcher" / EXENAME;
	if(fs::exists(launcherPath) && !isInGameFolder) {
		std::cout << "Launcher binary found in game folder, running that." << std::endl;
		RunLauncher(launcherPath);
		return 0;
	}


	SDL_Thread *guiThread = SDL_CreateThread(doGui, "Gui", (void *)(&steamPath));

	// if(runFromGame)
	// g.simulateButton(BUT_CLICKED_INSTALL);




	TRYCATCHERR_START()




	//std::cout << steam.getApp(440)->getName() << std::endl;
	//std::cout << steam.getApp(440)->getInstallPath() << std::endl;

	if(!fs::exists(of)) {
		fs::create_directories(of);
	}



	fs::current_path(of);

	checkDirsExist();
	TRYCATCHERR_END("Could not find or set directory correctly.")

	OFSNet net("http://svn.openfortress.fun/launcher/files", gameFolderName);
	//OFSNet net("http://127.0.0.1/", gameFolderName);

	// To Fenteale: This should be called the moment that the "Update"
	// button is pressed.
	net.fetchDatabase();

	OFSDatabase db(&net);

	OFSImportSVN svn(fs::current_path(), &db);
	std::cout << "Is this an SVN import? " << svn.isSVN() << std::endl;

	if(svn.isSVN()) {
		if(OFSYesNoDialog("SVN Install Detected.", "An SVN install of Open Fortress has been detected.\n\n"
												   "Import and update this install?") == 0) {
			simulateButton(BUT_CLICKED_VERIFYINTEGRITY);

			SDL_SemWait(verifyStateLock);
			verifyState = -1;
			SDL_SemPost(verifyStateLock);
			std::cout << "Verifying integrity..." << std::endl;
			int vi = svn.convertSVN();;
			std::cout << vi << std::endl;
			SDL_SemWait(verifyStateLock);
			verifyState = vi;
			SDL_SemPost(verifyStateLock);
		}
	}


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

				db.downloadFiles(progData, &butStateData);
				c = continueData;

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
				else
					simulateButton(INSTALL_FINISHED);

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

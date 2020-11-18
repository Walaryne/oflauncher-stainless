//
// Created by fenteale on 10/23/20.
//

#include "OFSGuiThread.h"


int doGui(void *ptr) {
	TRYCATCHERR_START()
	OFSUserSettings us(*((std::string*)(ptr)));
	//us.setLaunchOpt(us.getUsers()[0], "-secure -steam");
	std::vector<OFSSteamUser> sU;
	sU = us.getUsers();

	std::string sp;
	OFSConfig cf;
	cf.loadFromDisk();
	OFSGui g;
	std::vector<std::string> userString;
	for(auto &u : sU)
		userString.push_back(u.name);
	g.setUsers(userString);
	float prog;
	while(g.loop()) {
		//set progress
		//SDL_SemWait(progDataLock);
		prog = progData;
		//SDL_SemPost(progDataLock);

		g.sendEvent("progress", EVENT_PROGBAR_UPDATE, std::make_shared<float>(prog));

		GuiActs a = g.getLastAct();
		if(a) {
			std::shared_ptr<void> data;
			bool updateState = true;
			switch(a) {
			case BUT_CLICKED_UPDATE_DIR:
				data = g.getData("dirChooser", DATA_DIR);
				if(data != nullptr)
					g.sendEvent("steamPath", EVENT_DATA_TEXT_UPDATE, data);
				updateState = false;
				break;
			case BUT_CLICKED_OPTIONS:
				cf.readValue("/steamPath", sp);
				g.sendEvent("steamPath", EVENT_DATA_TEXT_UPDATE, std::make_shared<std::string>(sp));
				//no break here, we actually want it to also perform the default action
				break;
			case BUT_CLICKED_SAVEOP:
				cf.writeValue("/steamPath", *std::static_pointer_cast<std::string>(g.getData("steamPath", DATA_TEXT)));
				cf.commitToDisk();
				break;
			case BUT_CLICKED_STEAMUSER:
				std::cout << g.getUser() << std::endl;
				for(auto &u : sU)
					if(u.name == g.getUser())
						us.setLaunchOpt(u, "-secure -steam");
				break;
			case INSTALL_FINISHED:
#ifdef __LINUX__
				if(firstTime)
					g.simulateButton(BUT_CLICKED_SHOW_STEAMUSER);
#endif
				break;
			default:
				break;
			}
			if(updateState)	{
				SDL_SemWait(butDataLock);
				butStateData = a;
				SDL_SemPost(butDataLock);
			}
		}
		if(verifyState>=0) {
			g.verified = verifyState;
			g.simulateButton(BUT_CLICKED_OPTIONS);
			SDL_SemWait(verifyStateLock);
			verifyState = -2;
			SDL_SemPost(verifyStateLock);
		}
	}
	TRYCATCHERR_END("OFSGui")
	SDL_SemWait(continueDataLock);
	continueData = false;
	SDL_SemPost(continueDataLock);
	return 0;
}
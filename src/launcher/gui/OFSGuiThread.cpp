//
// Created by fenteale on 10/23/20.
//

#include "OFSGuiThread.h"


int doGui(void *ptr) {
	TRYCATCHERR_START()
	std::string sp;
	OFSConfig cf;
	cf.loadFromDisk();
	OFSGui g;
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
				std::shared_ptr<std::string> spT = std::static_pointer_cast<std::string>(g.getData("steamPath", DATA_TEXT));
				std::cout << *spT << std::endl;
				cf.writeValue("/steamPath", *spT);
				cf.commitToDisk();
				break;
			}
			if(updateState)	{
				SDL_SemWait(butDataLock);
				butStateData = a;
				SDL_SemPost(butDataLock);
			}
		}
	}
	TRYCATCHERR_END("OFSGui")
	SDL_SemWait(continueDataLock);
	continueData = false;
	SDL_SemPost(continueDataLock);
	return 0;
}
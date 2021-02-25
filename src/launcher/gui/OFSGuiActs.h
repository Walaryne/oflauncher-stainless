#ifndef OFLAUNCHER_STAINLESS_OFSGUIACTS_H
#define OFLAUNCHER_STAINLESS_OFSGUIACTS_H

//#include "SDL2/SDL.h"
#include <string>
#include <memory>
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

enum GuiActs { // Add an activity name here
	NOT_CLICKED,
	BUT_CLICKED_UPDATE_DIR,
	BUT_CLICKED_OPTIONS,
	BUT_CLICKED_MAIN,
	BUT_CLICKED_SAVEOP,
	BUT_CLICKED_UPDATEGAMEINFO,
	BUT_CLICKED_VERIFYINTEGRITY,
	BUT_CLICKED_INSTALL,
	BUT_CLICKED_PN,
	BUT_CLICKED_CANCEL,
	BUT_CLICKED_LAUNCH,
	INSTALL_FINISHED,
	VERIFY_FINISHED,
	BUT_CLICKED_SHOW_STEAMUSER,
	BUT_CLICKED_STEAMUSER,
	DATA_TEXT,
	DATA_DIR
};

enum GuiEvents {
	NO_EVENT,
	EVENT_SDL,
	EVENT_PROGBAR_UPDATE,
	EVENT_DATA_TEXT,
	EVENT_DATA_TEXT_UPDATE,
	EVENT_DATA_DIR
};

class OFSGuiEvent {
public:
	OFSGuiEvent(const std::string name, GuiEvents eventType, std::shared_ptr<void> data) : name(name), eventType(eventType), data(data) {}
	const std::string name;
	GuiEvents eventType;
	// * data;
	std::shared_ptr<void> data;
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIACTS_H
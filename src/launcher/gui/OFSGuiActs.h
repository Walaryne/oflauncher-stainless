#ifndef OFLAUNCHER_STAINLESS_OFSGUIACTS_H
#define OFLAUNCHER_STAINLESS_OFSGUIACTS_H

#include <SDL2/SDL.h>
#include <string>
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

enum GuiActs { // Add an activity name here
	NOT_CLICKED,
	BUT_CLICKED_UPDATE,
	BUT_CLICKED_OPTIONS,
	BUT_CLICKED_MAIN,
	BUT_CLICKED_INSTALL,
	BUT_CLICKED_CANCEL,
	DATA_TEXT
};

enum GuiEvents {
	NO_EVENT,
	EVENT_SDL,
	EVENT_PROGBAR_UPDATE,
	EVENT_DATA_TEXT
};

class OFSGuiEvent {
public:
	OFSGuiEvent(const std::string name, GuiEvents eventType, void* data) : name(name), eventType(eventType), data(data) {}
	const std::string name;
	GuiEvents eventType;
	void * data;
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIACTS_H
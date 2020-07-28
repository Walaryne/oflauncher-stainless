#ifndef OFLAUNCHER_STAINLESS_OFSGUIACTS_H
#define OFLAUNCHER_STAINLESS_OFSGUIACTS_H

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

enum GuiActs { // Add an activity name here
	NOT_CLICKED,
	BUT_CLICKED_UPDATE,
	TAB_CLICKED_OPTIONS,
	TAB_CLICKED_MAIN,
	BUT_CLICKED_INSTALL,
	BUT_CLICKED_CANCEL
};

enum GuiEvents {
	NO_EVENT,
	EVENT_SDL,
	EVENT_PROGBAR_UPDATE
};

class OFSGuiEvent {
public:
	OFSGuiEvent();
	OFSGuiEvent(SDL_Event *sdl) : sdl(*sdl), eventType(EVENT_SDL), data(nullptr) {}
	OFSGuiEvent(GuiEvents eventType, void* data) : eventType(eventType), data(data) {}
	SDL_Event sdl;
	GuiEvents eventType;
	void * data;
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIACTS_H
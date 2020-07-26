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

enum GuiEventEnum {
	MOUSE_DOWN, // FOCUS ONLY
	MOUSE_UP,	// FOCUS ONLY
	MOUSE_MOVE	// FOCUS ONLY
};

struct GuiEvent {
	GuiEventEnum type;
	virtual ~GuiEvent() {}
};

struct MouseGuiEvent : GuiEvent {
	int x, y;
	virtual ~MouseGuiEvent() {}
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIACTS_H
//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGUI_H
#define OFLAUNCHER_STAINLESS_OFSGUI_H

#include "SDL2/SDL.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class OFSGui;

typedef void (*GuiButtonFunction)(void);
typedef void (*GuiButtonMethod)(OFSGui *);

#define DEFINE_LAYOUT_H(fname)                                                 \
	static void fname(OFSGui *o);                                              \
	void fname()

enum GuiActs { // Add an activity name here
	NOT_CLICKED,
	BUT_CLICKED_UPDATE,
	TAB_CLICKED_OPTIONS,
	TAB_CLICKED_MAIN
};

class OFSGuiImage {
protected:
	SDL_Texture *texture;
	SDL_Rect src;
	SDL_Rect size;
	bool ok;
	int subImages;

public:
	OFSGuiImage(const std::string &image_file, SDL_Renderer *renderer,
				const int &x, const int &y, const int &NumOfSubImages);
	~OFSGuiImage();
	bool isOk();
	SDL_Texture *getTexture();
	void renderCopy(SDL_Renderer *renderer);
	void setIndex(const int &i);
	virtual void getClickedDown();
	virtual GuiActs getClickedUp();
	virtual void getHover();
};

class OFSGuiButton : public OFSGuiImage {
private:
	GuiActs act;
	bool isClicked;

public:
	OFSGuiButton(const std::string &image_file, SDL_Renderer *renderer,
				 GuiActs actToLink, const int &x, const int &y,
				 const int &NumOfSubImages);
	~OFSGuiButton();
	void getClickedDown();
	GuiActs getClickedUp();
	void getHover();
};

class OFSGui {
private:
	SDL_Window *window;
	// SDL_Surface *surface; // depricated because of renderer.  maybe delete
	// later if its seriously not needed
	SDL_Renderer *renderer;
	std::vector<std::unique_ptr<OFSGuiImage>> imgs;
	bool ok;
	std::string err{};
	bool e_quit;

	std::unordered_map<int, GuiButtonFunction> bindFuncs;
	std::unordered_map<int, GuiButtonMethod> bindMeths;

	void setError(const std::string &err_msg_pre);

	// layout construction helper methods
	void addImage(const std::string &image_file, const int &x = 0,
				  const int &y = 0, const int &NumOfSubImages = 0);
	void addButton(const std::string &image_file, GuiActs actToLink,
				   const int &x, const int &y, const int &NumOfSubImages);
	void setLastIndex(const int &i);
	void clearLayout();

	// layouts
	DEFINE_LAYOUT_H(setupLayout);
	DEFINE_LAYOUT_H(setupLayoutOptions);

public:
	OFSGui();
	~OFSGui();
	bool isOk();
	std::string getError();

	void bindActivity(GuiActs actToBind, GuiButtonFunction funcPoint);
	void bindActivity(GuiActs actToBind, GuiButtonMethod funcPoint);

	bool loop();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUI_H

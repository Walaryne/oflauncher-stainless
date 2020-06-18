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

typedef void (*GuiButtonFunction)(void);

enum GuiActs { // Add an activity name here
	NOT_CLICKED,
	BUT_CLICKED_PLAY
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
	virtual GuiActs getClicked();
};

class OFSGuiButton : public OFSGuiImage {
private:
	GuiActs act;
	bool canBeClicked;

public:
	OFSGuiButton(const std::string &image_file, SDL_Renderer *renderer,
				 GuiActs actToLink, const int &x, const int &y,
				 const int &NumOfSubImages);
	~OFSGuiButton();
	GuiActs getClicked();
};

class OFSGui {
private:
	SDL_Window *window;
	SDL_Surface *surface; // depricated because of renderer.  maybe delete later
						  // if its seriously not needed
	SDL_Renderer *renderer;
	std::vector<std::unique_ptr<OFSGuiImage>> imgs;
	bool ok;
	std::string err{};
	bool e_quit;

	std::unordered_map<int, GuiButtonFunction> bindFuncs;

	void setError(const std::string &err_msg_pre);

public:
	OFSGui();
	~OFSGui();
	bool isOk();
	std::string getError();

	void bindActivity(GuiActs actToBind, GuiButtonFunction funcPoint);

	bool loop();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUI_H

//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGUI_H
#define OFLAUNCHER_STAINLESS_OFSGUI_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef INCLUDE_RESOURCES
#include <filesystem>
namespace fs = std::filesystem;
#endif

#include "OFSGuiActs.h"
#include "OFSGuiError.h"

#include "OFSGuiButton.h"
#include "OFSGuiDirButton.h"
#include "OFSGuiImage.h"
#include "OFSGuiProgBar.h"
#include "OFSGuiSpinny.h"
#include "OFSGuiText.h"
#include "OFSGuiTextEntry.h"
#include "res/EmbedData.h"

class OFSGui;

typedef void (*GuiButtonFunction)(void);
typedef void (*GuiButtonMethod)(OFSGui *);

#define DEFINE_LAYOUT_H(fname)                                                 \
	static void fname(OFSGui *o);                                              \
	void fname()

class OFSGui {
private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
	std::vector<std::unique_ptr<OFSGuiImage>> _imgs;
	std::vector<std::shared_ptr<OFSGuiEvent>> _evs;
	bool _quit;

	std::unordered_map<GuiActs, bool> _actStates;
	GuiActs _currAct;
	std::unordered_map<int, GuiButtonMethod> _bindMeths;

#ifndef INCLUDE_RESOURCES
	fs::path _orig_path;
	fs::path _new_path;
#endif

	void bindActivity(GuiActs actToBind, GuiButtonMethod funcPoint);

	// layout construction helper methods
	void addImage(const std::string &name, resData data, const int &x = 0, const int &y = 0,
				  const int &NumOfSubImages = 0);
	void addButton(const std::string &name, resData fontData, GuiActs actToLink, const std::string& text, const int &x,
				   const int &y, const ButtonTypes& bType);
	void addDirButton(const std::string &name, resData fontData, const int &x,
					  const int &y, const ButtonTypes& bType);
	void addText(const std::string &name, resData fontData, const std::string &text = "", const int &text_size = 20,
				 const int &x = 0, const int &y = 0);
	void addTextEntry(const std::string &name, resData fontData, const std::string &text = "", const int &x = 0,
					  const int &y = 0, const int &width = 100, const bool& startFocused = false);
	void addSpinny(const std::string &name, resData data, const int &x = 0, const int &y = 0);
	void addProgressBar(const std::string &name, resData data, const int &x = 0, const int &y = 0,
						const int &width = 50);
	void clearLayout();

	// layouts
	/*
	DEFINE_LAYOUT_H(setupLayout);
	DEFINE_LAYOUT_H(setupLayoutOptions);
	*/
	DEFINE_LAYOUT_H(preInstallLayout);
	DEFINE_LAYOUT_H(installLayout);
	DEFINE_LAYOUT_H(SteamDirOption);

public:
	OFSGui();
	~OFSGui();

	// void bindActivity(GuiActs actToBind, GuiButtonFunction funcPoint);
	bool ifActivity(GuiActs actToCheck);
	GuiActs getLastAct();

	bool simulateButton(GuiActs actToSim);

	void setProgress(const float &progress);

	bool loop();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUI_H

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

	//maybe could do this better in the future:
	std::vector<std::string> _usersString;
	std::string _selectedUser;




	void bindActivity(GuiActs actToBind, GuiButtonMethod funcPoint);

	// layout construction helper methods
	void addImage(const std::string &name, resData data, const int &x = 0, const int &y = 0,
				  const int &NumOfSubImages = 0);
	void addButton(const std::string &name, resData fontData, GuiActs actToLink, const std::string& text, const int &x,
				   const int &y, const int textSize);
	void addButtonArray(resData fontData, GuiActs actToLink, const int &x,
						const int &y, const int textSize);
	void addImgButton(const std::string &name, resData imgData, resData imgDataSel, GuiActs actToLink, const int &x, const int &y, const ButtonTypes& bType);
	void addDirButton(const std::string &name, resData fontData, resData imgDataSel, GuiActs actToLink, const int &x,
					  const int &y, const ButtonTypes& bType);
	void addText(const std::string &name, resData fontData, const std::string &text = "", const int &text_size = 20,
				 const int &x = 0, const int &y = 0);
	void addTextEntry(const std::string &name, resData fontData, const std::string &text = "", const int &x = 0,
					  const int &y = 0, const int &width = 100, const bool& startFocused = false);
	void addSpinny(const std::string &name, resData data, const int &x = 0, const int &y = 0);
	void addProgressBar(const std::string &name, resData data, GuiActs act, const int &x = 0, const int &y = 0,
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
	DEFINE_LAYOUT_H(postInstall);
	DEFINE_LAYOUT_H(selectUser);
	DEFINE_LAYOUT_H(verifyFiles);
	DEFINE_LAYOUT_H(postVerifyFiles);
	DEFINE_LAYOUT_H(quitLayout);

public:
	OFSGui();
	~OFSGui();

	// void bindActivity(GuiActs actToBind, GuiButtonFunction funcPoint);
	bool ifActivity(GuiActs actToCheck);
	GuiActs getLastAct();

	bool simulateButton(GuiActs actToSim);

	void sendEvent(std::string name, GuiEvents event, std::shared_ptr<void> data);
    std::shared_ptr<void> getData(const std::string &name, GuiActs event);

	void setUsers(std::vector<std::string> users) {_usersString = users; }
	std::string getUser() {return _selectedUser;}

	bool loop();

	void quit();

	//WARNING WARNING: LAZY!!!
	int verified;
};

#endif // OFLAUNCHER_STAINLESS_OFSGUI_H

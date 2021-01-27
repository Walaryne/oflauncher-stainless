//
// Created by walaryne on 6/14/20.
//

#include "OFSGui.h"

//########### OFSGui ############
OFSGui::OFSGui() {

	_quit = false;
	_actStates.emplace(NOT_CLICKED, false);

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		throw SDLException("Can't Init SDL");

	_window =
		SDL_CreateWindow("Open Fortress Launcher", SDL_WINDOWPOS_UNDEFINED,
						 SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
						 SDL_WINDOW_SHOWN | SDL_WINDOW_UTILITY);
	// On my computer, I have "unredir-if-possible" enabled in my picom
	// config, and this program causes that to trigger unless you have the
	// SDL_WINDOW_UTILIY flag lol
	if(!_window)
		throw SDLException("Cannot create window");

	_renderer = SDL_CreateRenderer(
		_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(_renderer == nullptr)
		throw SDLException("Can't create renderer");

	SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0xFF, 0xFF);
	if(TTF_Init() == -1)
		throw SDLTTFException("Can't Init SDL_ttf");

	preInstallLayout();

	SDL_StartTextInput();
}

OFSGui::~OFSGui() {
	SDL_StopTextInput();
	_imgs.clear();
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool OFSGui::ifActivity(GuiActs actToCheck) {
	bool ret = _actStates[actToCheck];
	_actStates[actToCheck] = false;
	return ret;
}
GuiActs OFSGui::getLastAct() {
	GuiActs ga = _currAct;
	_currAct = NOT_CLICKED;
	return ga;
}
void OFSGui::bindActivity(GuiActs actToBind, GuiButtonMethod funcPoint) {
	_bindMeths.emplace(actToBind, funcPoint);
}

bool OFSGui::simulateButton(GuiActs actToSim) {
	bool ret = false;
	if(_actStates.count(actToSim))
		_actStates[actToSim] = true;
	else
		_actStates.emplace(actToSim, true);
	if(_bindMeths[actToSim]) {

		_bindMeths[actToSim](this);
		ret = true;

	}
	return ret;
}

void OFSGui::sendEvent(std::string name, GuiEvents event, std::shared_ptr<void> data) {
	_evs.emplace_back(std::make_shared<OFSGuiEvent>(name, event, data));
}

std::shared_ptr<void> OFSGui::getData(const std::string &name, GuiActs event) {
	for(auto &x : _imgs)
	{
		OFSGuiEvent e = x->getData(event);
		if(e.eventType != NO_EVENT)
			if(e.name == name)
				return e.data;
	}
	return nullptr;
}

bool OFSGui::loop() {  //the main loop thats called once every frame

	SDL_Event e;

	std::vector<GuiActs> actStack;  //this is our queue of acts fired by the elements

	while(SDL_PollEvent(&e)) {
		//This loops for each event that hasn't been processed yet.
		if(e.type == SDL_QUIT)
			_quit=true;
		else {
            std::shared_ptr<void>buffer = std::make_shared<SDL_Event>(e);
            //make a copy of this event and add it into the queue of events
			sendEvent("all", EVENT_SDL, buffer);
		}
	}

	//iterate through all the elements and pass all the events into them
	for(auto &i : _imgs)
	{
		for(auto &ev : _evs) {
			GuiActs a = i->parseEvents(ev);
			if(a != NOT_CLICKED) {
				if(a==BUT_CLICKED_STEAMUSER)
					_selectedUser=i->getName();
				actStack.push_back(a);
			}
		}
	}

	_evs.clear(); //clear event queue

	for(auto act : actStack)
	{
		_currAct = act;
		simulateButton(act);  //switch layouts
	}
	actStack.clear();

	SDL_RenderClear(_renderer);
	for(auto &i : _imgs) {
		i->renderCopy(_renderer);  //call each element's render function
	}
	SDL_RenderPresent(_renderer);

	return !_quit;
}

void OFSGui::quit() { _quit = true; }

//Functions for layout creation
void OFSGui::addImage(const std::string &name, resData data, const int &x, const int &y,
					  const int &NumOfSubImages) {
	_imgs.push_back(
		std::make_unique<OFSGuiImage>(name, data, _renderer, x, y, NumOfSubImages));
}
void OFSGui::addButton(const std::string &name, resData fontData, GuiActs actToLink, const std::string& text, const int &x = 0,
					   const int &y = 0, const int textSize = 30) {
	_imgs.push_back(std::make_unique<OFSGuiButton>(name, fontData, _renderer, actToLink,
												   x, y, text, textSize));
}

void OFSGui::addButtonArray(resData fontData, GuiActs actToLink, const int &x,
						 const int &y, const int textSize = 30) {
	int currY = y;
	for(auto &n : _usersString)	{
		addButton(n, fontData, actToLink, n, x,	currY, textSize);
		currY += 30;
	}
}

void OFSGui::addImgButton(const std::string &name, resData imgData, resData imgDataSel, GuiActs actToLink, const int &x = 0, const int &y = 0, const ButtonTypes& bType = DEFAULT_BUTTON) {
	_imgs.push_back(std::make_unique<OFSGuiButton>(name, imgData, imgDataSel, _renderer, actToLink,
												   x, y, bType));
}

void OFSGui::addDirButton(const std::string &name, const EmbedData fontData, const EmbedData imgDataSel, GuiActs actToLink, const int &x, const int &y, const ButtonTypes &bType) {
	_imgs.push_back(std::make_unique<OFSGuiDirButton>(name, fontData, imgDataSel, _renderer, actToLink, x, y, bType));
}

void OFSGui::addText(const std::string &name, resData fontData, const std::string &text, const int &text_size,
					 const int &x, const int &y) {
	_imgs.push_back(
		std::make_unique<OFSGuiText>(name, fontData, _renderer, text, text_size, x, y));
}
void OFSGui::addTextEntry(const std::string &name, resData fontData, const std::string &text, const int &x, const int &y,
						  const int &width, const bool& startFocused) {
	_imgs.push_back(
		std::make_unique<OFSGuiTextEntry>(name, fontData, _renderer, text, x, y, width));
}
void OFSGui::addSpinny(const std::string &name, resData data, const int &x, const int &y) {
	_imgs.push_back(std::make_unique<OFSGuiSpinny>(name, data, _renderer, x, y));
}

void OFSGui::addProgressBar(const std::string &name, resData data, GuiActs act, const int &x, const int &y,
							const int &width) {
	_imgs.push_back(
		std::make_unique<OFSGuiProgBar>(name, data, _renderer, act, x, y, width));
}

void OFSGui::clearLayout() {
	_imgs.clear();
	// bindFuncs.clear();
	_bindMeths.clear();
}

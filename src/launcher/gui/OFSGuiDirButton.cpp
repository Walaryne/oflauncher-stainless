//
// Created by fenteale on 8/2/20.
//

#include "OFSGuiDirButton.h"

OFSGuiDirButton::OFSGuiDirButton(const std::string &name, const EmbedData imgData, SDL_Renderer *renderer, GuiActs actToLink, const int &x, const int &y, const ButtonTypes &buttonType) :
 OFSGuiButton(name, imgData, renderer, actToLink, x, y, buttonType){

}

void OFSGuiDirButton::_clickedOnAction() {
	nfdchar_t *outPath = nullptr;
	NFD_PickFolder( nullptr, &outPath);
	if(outPath) {
		_path.clear();
		_path.append(outPath);
	}
}

OFSGuiEvent OFSGuiDirButton::getData(GuiActs typeToGet) {
	if(typeToGet == DATA_DIR)
		return OFSGuiEvent(_name, EVENT_DATA_DIR, (void*)(&_path));

	return OFSGuiEvent("", NO_EVENT, nullptr);
}
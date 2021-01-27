#include "OFSGuiProgBar.h"
#include "res/barL.bmp.h"
#include "res/barM_n.bmp.h"
#include "res/barR.bmp.h"
#include <iostream>


#define DATA(res_name) res_name##_bmp_data

#define PIX_DRAW_PAST                                                          \
	2 // how many pixels to start drawing the loading bar progress into the end
	  // caps



OFSGuiProgBar::OFSGuiProgBar(const std::string &name, resData data, SDL_Renderer *renderer, GuiActs act, const int &x,
							 const int &y, const int &width)
	: OFSGuiImage(name, data, renderer, x, y, 0) {

	_renderer = renderer;

	_leftcap = _loadSecondImg(DATA(barL), &_leftSrc, &_leftSize);
	_rightcap = _loadSecondImg(DATA(barR), &_rightSrc, &_rightSize);
	_middleNone = _loadSecondImg(DATA(barM_n), &_mnSrc, &_mnSize);

	_barWidth = (width - _leftSize.w - _rightSize.w) + (PIX_DRAW_PAST * 2);
	if(x < 0)
		_xPos = (WINDOW_WIDTH / 2) - (width / 2);
	else
		_xPos = x;

	_leftSize.x = _xPos;
	_leftSize.y = y;
	_rightSize.x = _xPos + width - _rightSize.w;
	_rightSize.y = y;
	_mnSize.y = y;

	_progress = 0;
	_act = act;
}

OFSGuiProgBar::~OFSGuiProgBar() {
	SDL_DestroyTexture(_leftcap);
	SDL_DestroyTexture(_rightcap);
	SDL_DestroyTexture(_middleNone);
}

void OFSGuiProgBar::renderCopy(SDL_Renderer *renderer) {
	int currProg = 0;
	int initialX = _xPos + _leftSize.w - PIX_DRAW_PAST;
	for(int x = initialX; x < initialX + _barWidth; x++) {
		if(currProg <= _progress) {
			_size.x = x;
			SDL_RenderCopy(renderer, _texture, &_src, &_size);
		} else {
			_mnSize.x = x;
			SDL_RenderCopy(renderer, _middleNone, &_mnSrc, &_mnSize);
		}
		currProg++;
	}
	SDL_RenderCopy(renderer, _leftcap, &_leftSrc, &_leftSize);
	SDL_RenderCopy(renderer, _rightcap, &_rightSrc, &_rightSize);
}

GuiActs OFSGuiProgBar::parseEvents(std::shared_ptr<OFSGuiEvent> ev)
{
	GuiActs ret = NOT_CLICKED;
	if(ev->eventType == EVENT_PROGBAR_UPDATE) {
		std::shared_ptr<float> progPercent = std::static_pointer_cast<float>(ev->data);
		_progress = _barWidth * *progPercent;
		if( *progPercent == 1.0f)
			ret = _act;
	}
	return ret;
}
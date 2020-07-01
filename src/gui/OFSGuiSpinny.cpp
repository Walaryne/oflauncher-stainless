#include "OFSGuiSpinny.h"

OFSGuiSpinny::OFSGuiSpinny(const EmbedData data,
						   SDL_Renderer *renderer, const int &x, const int &y)
	: OFSGuiImage(data, renderer, x, y, 0) {
	_prevTick = SDL_GetTicks();
	_angle = 0;
}

OFSGuiSpinny::~OFSGuiSpinny() {
}

void OFSGuiSpinny::renderCopy(SDL_Renderer *renderer) {
	_angle += 0.5 * (SDL_GetTicks() - _prevTick);
	_prevTick = SDL_GetTicks();
	SDL_RenderCopyEx(renderer, _texture, &_src, &_size, _angle, nullptr,
					 SDL_FLIP_NONE);
}

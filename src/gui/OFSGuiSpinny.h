#ifndef OFLAUNCHER_STAINLESS_OFSGUISPINNY_H
#define OFLAUNCHER_STAINLESS_OFSGUISPINNY_H

#include "SDL2/SDL.h"
#include <string>

#include "OFSGuiImage.h"

class OFSGuiSpinny : public OFSGuiImage {
private:
	int _prevTick;
	double _angle;

public:
	OFSGuiSpinny(const std::string &image_file, SDL_Renderer *renderer,
				 const int &x = 0, const int &y = 0);
	~OFSGuiSpinny();
	void renderCopy(SDL_Renderer *renderer);
};

#endif // OFLAUNCHER_STAINLESS_OFSGUISPINNY_H
#pragma once
#include "header.h"
#include "SDL.h"

class Explosion
{
private:
	bool animated = false;
	int frames = 0;
	int speed = 100;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	Explosion();
	Explosion(const char* url, int f, int s) {
		animated = true;
		frames = f;
		speed = s;
	}

	void update() {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
	}
};
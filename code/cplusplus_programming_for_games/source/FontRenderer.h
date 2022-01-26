
#pragma once
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>

class FontRenderer
{
public:
	FontRenderer(SDL_Renderer* sdlRenderer, int _screenWidth, int _screenHeight);

	void init();
	void render(std::string text, int x, int y, int w, int h);
	void clean();

private:
	SDL_Renderer* renderer;
	TTF_Font* font = nullptr;
	int screenWidth = 0;
	int screenHeight = 0;
};


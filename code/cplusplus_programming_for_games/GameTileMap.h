#pragma once
#include <iostream>
#include <fstream>
#include <cctype>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class GameTileMap
{
public:
	GameTileMap(SDL_Renderer* rend) :renderer(rend) {};

	bool openMap();

private:
	SDL_Renderer* renderer;
	SDL_Texture* texture; 
	std::string fileName;
};


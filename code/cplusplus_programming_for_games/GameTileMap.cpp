#include "GameTileMap.h"

bool GameTileMap::openMap()
{
	SDL_Surface* image = IMG_Load(fileName.c_str());
	if (image == NULL) {
		std::cout << "Cannot ld tile image %s ", SDL_GetError();
		return -1;
	}

	// pixels = image dimension divided by nr of tiles 

	//std::cout << "sourceTileSizePx " << sourceTileSizePx << std::endl;

	// create a texture on the renderer from the image
	texture = SDL_CreateTextureFromSurface(renderer, image);

	//std::cout << "tileWidth " << *screenHeight << std::endl;

	// free the surface 
	SDL_FreeSurface(image);

	int map[100][100];

	
	std::ifstream openFile("mapFile.txt");
	if (openFile.is_open()) {
		// loop till end of file
		while (!openFile.eof())
		{
			std::string str;
			openFile >> str;

			char x = str[0], y = str[2];
			if (!isdigit(x) || !isdigit(y))
			{
				//
			}
		}

	}
	openFile.close();
}

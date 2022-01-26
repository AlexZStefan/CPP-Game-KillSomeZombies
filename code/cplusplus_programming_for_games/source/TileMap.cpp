#include "TileMap.h"

TileMap::TileMap(SDL_Renderer* sdlRenderer, std::string titleMapFilename, int& _screenWidth, int& _screenHeight, int sellectMap)
{
	renderer = sdlRenderer;
	screenWidth = &_screenWidth;
	screenHeight = &_screenHeight;
	fileName = titleMapFilename;
	tileMapSellection = sellectMap;	
}

int TileMap::init() {
	LoadMap("baseMap.map");

	//std::cout << "screenHeight " << *screenHeight << std::endl;

	// load the image onto a surface
	SDL_Surface* image = IMG_Load(fileName.c_str());
	if (image == NULL) {
		std::cout << "Cannot ld tile image %s ", SDL_GetError();
		return -1;
	}

	// pixels = image dimension divided by nr of tiles 
	sourceTileSizePx = image->w / 8;
	//std::cout << "sourceTileSizePx " << sourceTileSizePx << std::endl;

	sourceRect.w = sourceTileSizePx;
	sourceRect.h = sourceTileSizePx;

	// create a texture on the renderer from the image
	texture = SDL_CreateTextureFromSurface(renderer, image);

	// free the surface 
	SDL_FreeSurface(image);
	image = 0;

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j< mapWidth; j++)
		{
			// add the tiles into an vector
			if (mapOver[i][j] == TreeLeftBottom || mapOver[i][j] == TreeRightBottom ||
				mapOver[i][j] == Grave || mapOver[i][j] == RockBig) {				
				tilesToBlock.push_back(SDL_Rect{ j * (tileWidth) * 2, (i * ((tileHeight)) * 2 + tileWidth/2) ,tileWidth*2,tileWidth });
			}
			// add the damagable tiles into an vector
			if (mapOver[i][j] == RockBig) {
				damagableTiles.push_back(Tile{ SDL_Rect{ j * (tileWidth) * 2, (i * ((tileHeight)) * 2) ,64,32 }, true, j,i});
			}
		}
	}	
	return 0;
};

void TileMap::clean()
{
	tilesToBlock.clear();
}

void TileMap::LoadMap(std::string path)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			mapFile.get(tile);

			newMap[y][x] = atoi(&tile);
			// ignores the next char
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void TileMap::render() {

	for (int col = 0; col < mapHeight; col++) {
		for (int row = 0; row < mapWidth; row++) {
			// sellects what map to render 0 = background map.
			// can be improved by rendering less tiles 
			if (tileMapSellection == 0)
			{
				sourceRect.x = (newMap[col][row] % 8) * sourceTileSizePx;
				sourceRect.y = (newMap[col][row] / 8) * sourceTileSizePx;
			}
			else
			{
				sourceRect.x = (mapOver[col][row] % 8) * sourceTileSizePx;
				sourceRect.y = (mapOver[col][row] / 8) * sourceTileSizePx;
			}

			SDL_Rect renderRect;
			
			renderRect.x = (row * (tileWidth)) * 2;
			renderRect.y = (col * (tileHeight)) * 2;
			renderRect.w = tileWidth * 2;
			renderRect.h = tileHeight * 2;

		SDL_RenderCopy(renderer, texture, &sourceRect, &renderRect);
	}
}
};

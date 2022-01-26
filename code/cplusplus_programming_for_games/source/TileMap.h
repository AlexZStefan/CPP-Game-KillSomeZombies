#pragma once
#include <iostream>
//#include <sdl.h>
#include <SDL_image.h>
#include <math.h> 
#include <fstream>
#include <string>
#include "Player.h"

struct Tile {
	SDL_Rect tile;
	bool render; 
	int xPos;
	int yPos;
};


enum TilesDef
{
	Grass = 0,
	Sand = 6,
	Gravel = 7,
	TreeLeftTop = 8,
	TreeRightTop = 9,
	TreeLeftBottom = 16,
	TreeRightBottom = 17,
	ForestBottomLeft = 32,
	ForestBottomRight = 33,
	Grave = 67,
	Cross = 68,
	RockSmall = 64,
	RockBig = 65,
};

const int mapWidth = 10;
const int mapHeight = 8;

class TileMap
{
public:
	TileMap(SDL_Renderer* sdlRenderer, std::string titleMapFilename, int& _screenWidth, int& _screenHeight, int sellectMap);
	int init();
	void render();
	void clean();
	void LoadMap(std::string path);
	
	std::vector<SDL_Rect> getTileRect() { return tilesToBlock; }
	std::vector<Tile>& getDamagableTileRect() { return damagableTiles; }

	int mapOver[mapHeight][mapWidth] = {
	{ForestBottomLeft,ForestBottomRight,ForestBottomLeft,ForestBottomRight,ForestBottomLeft,ForestBottomRight,ForestBottomLeft,ForestBottomRight,ForestBottomLeft,ForestBottomRight},
	{TreeLeftBottom,TreeRightBottom,TreeLeftBottom,TreeRightBottom,TreeLeftBottom,TreeRightBottom,TreeLeftBottom,TreeRightBottom,TreeLeftBottom,TreeRightBottom},
	{Grave,Sand,Cross,Grave,Grave,Grass,Grass,Cross,Sand,Sand},
	{Grass,Grass,RockBig,Grass,Grass,Sand,Grass,Grass,Grass,Grass},
	{Gravel,Gravel,Gravel,Gravel,Gravel,Gravel,Gravel,Gravel,Gravel,Gravel},
	{Sand,Sand,RockBig,Sand,Sand,Sand,Sand,Sand,Sand,Sand},
	{Grass,Grass,RockBig,Grass,Grass,Grass,RockBig,Grass,Grass,Grass},
	{1,1,1,1,RockBig,1,1,1,1,1}
	};

	int newMap[mapHeight][mapWidth]
	{
		0
	};
		
private:
	int tileMapSellection;
	int* screenWidth;
	int* screenHeight;
	int tileType;
	std::vector <SDL_Rect> tilesToBlock;
	std::vector <Tile> damagableTiles;

	int sourceTileSizePx;
	const int tileWidth = 32;
	const int tileHeight = 32;

	std::string fileName;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect sourceRect;
};


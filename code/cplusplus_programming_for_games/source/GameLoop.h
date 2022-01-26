#pragma once


#define SDL_MAIN_HANDLED

#include "FontRenderer.h"
#include "TileMap.h"
#include "Functions.h"
#include "GunFire.h"
#include "EnemyManager.h"
#include "GameUI.h"
#include "Collectables.h"
#include "SoundPlayer.h"
#include "ParticleSystem.h"

#include <SDL.h>
#include <SDL_image.h>
#include <math.h>

#include "BulletManager.h"
#include <iostream>
#include <SDL_ttf.h>
#include <string>

class GameLoop {
public:
	GameLoop();

	int init();

	void update();

	void bulletCollision(std::vector <Bullet*> playerAmmo, SDL_Rect& playerRct);

	void tileMapCollision();

	void render();

	bool keepAlive();

	SDL_bool collision(SDL_Rect &value,SDL_Rect &rect2);

	void quitGame();

	void handleInput(SDL_Scancode& keyScanCode, SDL_Event& event);

	void clean();

	void pauseGame();

	SDL_Renderer* getRenderer() { return renderer; }

	int screenHeight = 512;
	int screenWidth = 640;	

private:
	bool isGamePaused = true;
	bool gameStarted = false;
	bool gameOver = false; 
	bool quitTheGame = false;

	SDL_Rect* tileRct;
	SDL_Rect* playerRct;

	ParticleSystem* particleSystem;
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Renderer* renderer = nullptr;

	GunFire* gunFire = nullptr;
	std::unique_ptr<GameUI> gameUI;
	FontRenderer* fontRenderer = nullptr;
	std::unique_ptr <TileMap> tileMap;
	std::unique_ptr <TileMap> overTileMap;
	std::unique_ptr <GameObject> myPlayer;
	std::unique_ptr <BulletManager> bm; 
	std::unique_ptr <EnemyManager> em; 
	std::unique_ptr <Collectables> collectables;	
	SoundPlayer* soundPlayer;

	std::vector<SDL_Rect> tilesNotWalkable;
	std::vector<Tile>* destroyableTiles;

	
	Player* player = nullptr;
	SDL_Rect* allObjects[];

};

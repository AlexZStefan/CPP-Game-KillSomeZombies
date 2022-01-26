#pragma once

#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <tuple>
#include <SDL_image.h>
#include "Functions.h"
#include <math.h>

class Player
{
	friend class Collectables;
	friend class EnemyManager;

public:
	Player(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHight);
	void init();
	void render();
	void update();
	void setHp(float dmg) { health -= dmg; };

	void clean();

	bool collision();

	void moveRight();

	void moveLeft();
	
	void moveUp();

	void moveDown();

	void PlayerHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);

	SDL_Rect &getRect() { return playerRect; };

	double getAngle() const;

	float &getHealth() { return health; };
	int &getScore() { return score; };
	void setScore(int value) { score += value; };
		
	std::tuple<float,float> position(){
		return  std::make_tuple(playerRect.x, playerRect.y);
	}
	
	int mouseX = 0;
	int mouseY = 0;

	int windowWidth;
	int windowHeight;
	
	SDL_Rect & getPlayerGun() { return playerGun;}

private:	
	int score = 0;
	float health = 1.f;
	float speed = 3;
	bool playerMoving;
	int playerWidth;
	int playerHeight;
	int pAnimation = 0;

	double angle = 0;
	float rotationAngle = 0;

	SDL_Rect playerRect;
	SDL_Rect playerGun; 
	SDL_Color  barBlue = { 255,0,0,100 };
	SDL_Color  barRed  = { 0,255,0,255 };

	std::vector<SDL_Texture*> playerText;
	
	SDL_Renderer* renderer;
	SDL_Texture* texture = nullptr;
};



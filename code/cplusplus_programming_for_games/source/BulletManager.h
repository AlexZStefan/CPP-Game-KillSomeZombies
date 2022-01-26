#pragma once
#include <SDL.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include "Player.h"
#include <iostream>
#include "GameObject.h"
#include "Functions.h"

const float TAU = M_PI * 2; 

class Bullet {
public:
	Bullet(float X, float Y, float r, float d) : x(X), y(Y), rotation(r), distance(d) {};

	~Bullet() { std::cout << "bullet destroyed" << std::endl; }

	float x = 0.0;
	float y = 0.0;
	float rotation;
	float rotationX;
	float rotationY;
	float distance;
	float radius = 5.0f; // have size of rect
	Circle circle = Circle(x,y,1.0f);
	SDL_Rect bulletRect = { 0, 0, 10,10 };

	bool render = false;
};

class BulletManager
{
	//friend class EnemyManager;
public:
	BulletManager(SDL_Renderer* renderer, Player* player) : renderer(renderer), player(player) {};

	void init();

	void shoot();

	auto getBullets() { return bullets; };

	void update();

	void draw();
	

	void clean();

	static void circ_rect_Collision(Circle& circ, SDL_Rect& rect);

	std::vector<Bullet*> getAmmo() { return bullets; };

private:
	int s = 0;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* bulletTexture = nullptr;
	std::vector <Bullet*> bullets; 
	
	Player* player = nullptr;

	const int SHOT_TIMER_MS = 300; 

	const int BULLET_VELOCITY = 15;
	unsigned int lastShot = 0; 
};



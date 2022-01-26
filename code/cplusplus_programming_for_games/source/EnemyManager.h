#pragma once
#include <SDL_image.h>
#include "Player.h"
#include <math.h>
#include <vector>

struct Enemy {
	float x = 0; 
	float y = 0;
	float rotation = 0.0f;

	void moveTo() {};
	void eAttack() {};
	void animate() {};

	bool render = true; 
	bool spawned = true; 

	SDL_Rect myRect = {60,60,60,60};
};

class EnemyManager
{
public:
	EnemyManager(SDL_Renderer* renderer, Player* player) : renderer(renderer), player(player) {};

	virtual ~EnemyManager(){}

	void spawner();
	void init();
	void render();

	void clean();
	void update();
	SDL_Rect& getRect() { return eRect; };
	std::vector <Enemy>& getEnemies() { return enemies; };

private:
	float playerX;
	float playerY;
	float* playerAngle;
	int animFrame = 0;
	SDL_Rect *playerRect;
	bool addEnemy1 = true;
	bool addEnemy2 = true;
	

	Player* player = nullptr;
	SDL_Renderer* renderer = nullptr; 

	SDL_Texture* texture = nullptr;
	std::vector<SDL_Texture*> zombieTexture;
	std::vector <Enemy> enemies;
	SDL_Rect eRect;
};



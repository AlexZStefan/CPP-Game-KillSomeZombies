#pragma once

#include "GameObject.h"
#include "Player.h"
#include <vector>;
#include "Functions.h"


class Collectables
{

public:
	Collectables(SDL_Renderer* rend);

	void spawn(SDL_Rect& enemyRect);
	void update(Player* player);
	void clean();
	void render();
	std::vector <GameObject>& getCollectables() { return coin; };

private:
	
	std::vector<GameObject> coin; 
	
	float x; 
	float y; 
	int spawnItem = 0;
	int value; 
	int health;

};


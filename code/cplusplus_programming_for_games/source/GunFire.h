#pragma once
#include "GameObject.h"
#include <list>

class GunFire:public GameObject
{
public:
	GunFire(const char* textureSheet, SDL_Renderer* rend);
	GunFire(const char* textureSheet, SDL_Renderer* rend,int xP, int yP);

	~GunFire() { };

	void update (int xPos, int yPos);
	void render(double playerAngle, SDL_Renderer* rend);

	void setRender(bool val) { rend = val; };
private:
	
	bool rend = false;
	
};


#pragma once
#include "GameObject.h"
#include <list>

class ParticleSystem:public GameObject
{
	
public:
	ParticleSystem(SDL_Renderer* rend);
	void Update();
	void Render(SDL_Surface* frameRender);
	~ParticleSystem() { SDL_FreeSurface(particleSurface); };

private:
	SDL_Surface* particleSurface;
	std::list<SDL_Rect> particlePostions;
	SDL_Renderer* renderer; 
	SDL_Texture* texture; 

	
	

	Uint32 emissionRate = 200;
	Uint32 emmisionRange = 90;
	Uint32 Gravity = 10;

	Uint32 lastParticleSpawn;
	Uint32 nextParticleSpawn;
};


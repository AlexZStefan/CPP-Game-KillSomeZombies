#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(SDL_Renderer* rend) :GameObject(rend)
{	
	renderer = rend;
	
	 this->setTexture("assets/snow.png");

	 texture = this->getTexture();
}

void ParticleSystem::Update()
{
	if (SDL_GetTicks() - lastParticleSpawn >= nextParticleSpawn)
	{
		lastParticleSpawn = SDL_GetTicks();
		nextParticleSpawn = emissionRate + (rand() % emmisionRange);
		SDL_Rect rct = { rand() %640 ,rand() % 640,5,5};
		
		particlePostions.push_back(rct);
		std::cout << particlePostions.size() << std::endl;
	}
	
	for (auto& particle : particlePostions) {
		particle.y += Gravity;
	
	}
	particlePostions.remove_if([](SDL_Rect rct) { return rct.y >= 500; });
}

void ParticleSystem::Render(SDL_Surface *frameRender)
{	
	for (auto& p : particlePostions)
	{
		SDL_BlitSurface(particleSurface, NULL, frameRender, &p);

		SDL_RenderCopy(renderer, texture, NULL, &p);
	}
}



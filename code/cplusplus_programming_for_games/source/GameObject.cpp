#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* rend)
{
	renderer = rend;
}

GameObject::GameObject(const char* textureSheet, SDL_Renderer* rend) {
	renderer = rend;
	textureSurf = IMG_Load(textureSheet);
	if (textureSurf == NULL) {
		std::cout << "Cannot ld image %s ", SDL_GetError();
		return;
	}
	objTexture = SDL_CreateTextureFromSurface(renderer, textureSurf);
	SDL_FreeSurface(textureSurf);

	xPos = -100;
	yPos = -100;
}

GameObject::GameObject(const char* textureSheet, SDL_Renderer* rend, int x, int y) {
	renderer = rend;
	textureSurf = IMG_Load(textureSheet);
	if (textureSurf == NULL) {
		std::cout << "Cannot ld image %s ", SDL_GetError();
		return;
	}
	objTexture = SDL_CreateTextureFromSurface(renderer, textureSurf);

	xPos = x;
	yPos = y;
	
	destRect.w = 20;
	destRect.h = 20;

	SDL_FreeSurface(textureSurf);
}

void GameObject::update() {			
	destRect.x = xPos;
	destRect.y = yPos;
}

void GameObject::render() {
	if (renderObject)
	SDL_RenderCopy(renderer, objTexture, NULL, &destRect);
}

void GameObject::clean()
{
	SDL_DestroyTexture(objTexture);
}

void GameObject::setTexture(const char* textureSheet)
{
	textureSurf = IMG_Load(textureSheet);

	objTexture = SDL_CreateTextureFromSurface(renderer, textureSurf);
}

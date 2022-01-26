#pragma once
#include <sdl.h>
#include <SDL_image.h>
#include <iostream>

class GameObject
{
	friend class Collectables;
	friend class Functions;

public:

	GameObject(SDL_Renderer* rend);

	GameObject(const char* textureSheet, SDL_Renderer* rend);
	GameObject(const char* textureSheet, SDL_Renderer* rend, int x, int y);
	
	virtual void update();
	
	virtual void render();

	void clean();

	SDL_Rect& objectRect() {
		return destRect;
	}

	void setRectPos(int val) { xPos = val; };
	void setRectYPos(int val) { yPos = val; };
	
	void setRenderStatus(bool state) { renderObject = state; };
	SDL_Texture *getTexture() { return objTexture; };
	void setTexture(const char* textureSheet);

private:
	int xPos; 
	int yPos;
	bool renderObject = true;
	SDL_Surface* textureSurf;
	SDL_Texture* objTexture; 
	SDL_Rect destRect;
	SDL_Renderer* renderer;
};

class Circle {
public:
	Circle(float X, float Y, float R) : y(Y), x(X), radius(R) { };
	float radius;
	float x;
	float y;
};

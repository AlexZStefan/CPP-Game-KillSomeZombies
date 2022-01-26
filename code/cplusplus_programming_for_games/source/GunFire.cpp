#include "GunFire.h"

GunFire::GunFire(const char* textureSheet, SDL_Renderer* rend):GameObject(textureSheet, rend)
{
	
}
GunFire::GunFire(const char* textureSheet, SDL_Renderer* rend,int xP, int yP) : GameObject(textureSheet, rend, xP, yP)
{

}

void GunFire::update(int xPos, int yPos)
{	
		setRectPos(xPos + 15);
		setRectYPos(yPos - 10);
		GameObject::update();
}

void GunFire::render(double playerAngle, SDL_Renderer* rend){
	
	if (this->rend == true)
	{
		SDL_Point playerSpin = { 5, 40 };
		SDL_RenderCopyEx(rend, getTexture(), NULL, &this->objectRect(), playerAngle, &playerSpin, SDL_FLIP_NONE);
	}
	this->rend = false;
}

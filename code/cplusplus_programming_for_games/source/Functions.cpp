#include "Functions.h"

SDL_bool Functions::collision(SDL_Rect& rect1, SDL_Rect& rect2)
{
	SDL_bool collision = SDL_HasIntersection(&rect1, &rect2);

	if (collision) std::cout << "Collided" << std::endl;

	return collision;
}

int Functions::randomNumber(int a, int b)
{
	std::random_device rd; // get random nr from hardwware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(a, b); // define range

	int number = distr(gen);
	return number;
}

bool Functions::circleCollision(float circX, float circY, float circRad, SDL_Rect& box)
{	
		//Closest point on collision box
		int collisionX, collisionY;
	
		//Find closest x offset
		if (circX < box.x)
		{
			collisionX = box.x;		
		}
		else if (circX > box.x + box.w)
		{
			collisionX = box.x + box.w;			
		}
		else
		{
			collisionX = circX;
		}
		if (circY < box.y)
		{
			collisionY = box.y;
		}
		else if (circY > box.y + box.h)
		{
			collisionY = box.y + box.h;
		}
		else
		{
			collisionY = circY;
		}

		//If the closest point is inside the circle
		if (Functions::distanceSquared(circX, circY, collisionX, collisionY) < (circRad * circRad))
		{
			// Shapes collided
			return true;
		}
		// No collision
		return false;	
}

double Functions::distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

bool Functions::myCollision(SDL_Rect& rect1, SDL_Rect& rect2)
{		
		if (rect1.x <= rect2.x + rect2.w &&
			rect1.x + rect1.w >= rect2.x &&
			rect1.y <= rect2.y + rect2.h &&
			rect1.y + rect1.h >= rect2.y)
		{	
			return true;
		}
		return false;
	}




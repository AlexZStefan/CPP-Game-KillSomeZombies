#include "BulletManager.h"

void BulletManager::init() {
	SDL_Surface* surface = IMG_Load("assets/lazer.png");
	this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
	if (bulletTexture == NULL) {
		std::cout << "bullet texture could not be loaded, %s", SDL_GetError();
	};	

	if (bullets.size() < 20)
	{
		for (int i = 0; i < 20; i++)
		{
			bullets.push_back(new Bullet( 315.0f, 230.0f, 0.0f, 0.0f ));			
			//std::cout <<"bullets.size" << bullets.size() << std::endl;
		}		
	}

	SDL_FreeSurface(surface);
}

void BulletManager::shoot() {
	if (s >= bullets.size()-1) s = 0;

	if (SDL_GetTicks() - lastShot > SHOT_TIMER_MS) {
		// get player position to update the bullet spawn location 
		std::tuple <float, float> playerPosition = player->position();
		float playerX = std::get<0>(playerPosition);
		float playerY = std::get<1>(playerPosition);

		float angle = float(player->getAngle());

		// modify one value only
		bullets[s]->bulletRect.x = playerX+20;
		bullets[s]->bulletRect.y = playerY+30;
		bullets[s]->distance = 0.0f;
		bullets[s]->rotationX = cos(angle * M_PI / 180.0f);
		bullets[s]->rotationY = sin(angle * M_PI / 180.0f);
		bullets[s]->render = true;
		++s;
		//std::cout << "bullets[s].x" << bullets[s]->x << std::endl;
		
		//std::cout << "playerX" << playerX << std::endl;
		lastShot = SDL_GetTicks();
	}
}

void BulletManager::update() {
		
	for (auto& b : bullets) {
		
		if (b->render == true)
		{			
			b->bulletRect.x += b->rotationY * BULLET_VELOCITY;

			//std::cout <<"b->rotation" << b->rotation << std::endl;
		
			b->bulletRect.y -= b->rotationX * BULLET_VELOCITY;
			b->distance += BULLET_VELOCITY;

			if (b->distance > 1000) b->render = false;
		}		

		//Functions::collision(b->r)
	}

	/*auto remove = std::remove_if(bullets.begin(), bullets.end(),[]
	(const Bullet& b) { return b.distance > 1000; });
	bullets.erase(remove, bullets.end());*/
}

void BulletManager::draw() {
	
	SDL_Point center = { -15 ,15 };	

	for (auto& b : bullets) {
		if (b->render == true)
		{				
			//SDL_RenderCopyEx(renderer, bulletTexture, NULL, &bulletRect, player->getAngle(), NULL, SDL_FLIP_NONE);

			SDL_SetRenderDrawColor(renderer, 100, 255, 111, 255);
			SDL_RenderFillRect(renderer, &b->bulletRect);
			SDL_RenderDrawRect(renderer, &b->bulletRect);
		}
	}
}

void BulletManager::clean() {
	SDL_DestroyTexture(this->bulletTexture);

	SDL_Renderer* renderer = nullptr;
	SDL_Texture* bulletTexture = nullptr;

	// delete the pointers and erase the pointers from the vector 
	for (int i = 0; i < 20; i++) {		
		delete bullets[0];
		bullets[0] = nullptr;
		bullets.erase(bullets.begin());

	}
	//std::cout<<	bullets.size() << std::endl;
	Player* player = nullptr;
}

void BulletManager::circ_rect_Collision(Circle& circ, SDL_Rect& rect)
{
	float cX, cY;

	for (int rectBox = 0; rectBox < ((rect.x + rect.w) & (rect.h + rect.y)); rectBox++)
	{
	}

	// square the r1+r2 
}

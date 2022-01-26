#include "EnemyManager.h"

void EnemyManager::spawner()
{
	for (auto& e : enemies) {
		if (e.spawned == true)
		{			
			e.spawned = false;
		}	

		if (e.render == false)
		{			
			e.render = true;
			
			int left = rand() % 2;
			if (left == 0)
			{
				player->getRect();
				e.myRect.x = (player->getRect().x + Functions::randomNumber(100, 200));
				e.myRect.y = (Functions::randomNumber(100, 500));
			}
			if (left == 1)
			{
				e.myRect.x = (player->getRect().x - Functions::randomNumber(100, 200));
				e.myRect.y = (Functions::randomNumber(100, 500));
			}			
		}
	}
}

void EnemyManager::init()
{
	SDL_Surface* surface = IMG_Load("assets/chibiCarlo2.png");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		std::cout << "SDL could not be loaded : " << SDL_GetError();
	}

	surface = IMG_Load("assets/zombie/skeleton_move_0.png");
	zombieTexture.push_back(SDL_CreateTextureFromSurface(renderer, surface));
	if (zombieTexture[0] == NULL) {
		std::cout << "SDL could not be loaded : " << SDL_GetError();
	}

	surface = IMG_Load("assets/zombie/skeleton_move_1.png");
	zombieTexture.push_back(SDL_CreateTextureFromSurface(renderer, surface));
	if (zombieTexture[1] == NULL) {
		std::cout << "SDL could not be loaded : " << SDL_GetError();
	}

	surface = IMG_Load("assets/zombie/skeleton_move_2.png");
	zombieTexture.push_back(SDL_CreateTextureFromSurface(renderer, surface));
	if (zombieTexture[2] == NULL) {
		std::cout << "SDL could not be loaded : " << SDL_GetError();
	}

	surface = IMG_Load("assets/zombie/skeleton_move_3.png");
	zombieTexture.push_back(SDL_CreateTextureFromSurface(renderer, surface));
	if (zombieTexture[3] == NULL) {
		std::cout << "SDL could not be loaded : " << SDL_GetError();
	}

	surface = IMG_Load("assets/zombie/skeleton_move_4.png");
	zombieTexture.push_back(SDL_CreateTextureFromSurface(renderer, surface));
	if (zombieTexture[4] == NULL) {
		std::cout << "SDL could not be loaded : " << SDL_GetError();
	}

	SDL_FreeSurface(surface);
	enemies.push_back(Enemy{});
	enemies.push_back(Enemy{});	
}

void EnemyManager::render()
{
	animFrame++;

	if (animFrame >= 20) animFrame = 0;
	for (auto& e : enemies) {		

		if (e.render == true)
		{
			SDL_RenderCopyEx(renderer, zombieTexture[animFrame /4], NULL, &e.myRect, e.rotation, NULL, SDL_FLIP_NONE);
		}
	}
}

void EnemyManager::clean()
{
	SDL_DestroyTexture(this->texture);

	for (int i = 0; i < 5; i++) {
		SDL_DestroyTexture(this->zombieTexture[0] );
		zombieTexture[0] = nullptr;
		zombieTexture.erase(zombieTexture.begin());
	}
	
	SDL_Renderer* renderer = nullptr;
	
	SDL_Texture* texture = nullptr;
	Player* player = nullptr;
}

void EnemyManager::update() {
	// get player position
	std::tuple <float, float> playerPos = player->position();
	playerX = std::get<0>(playerPos);
	float playerY = std::get<1>(playerPos);

	int windowX = player->windowHeight / 2;
	int windowY = player->windowWidth / 2;

	// get player angle to make the enamy face the player
	playerRect = &player->getRect();

	if (addEnemy1 == true)
	{
		if (addEnemy2 == true)
		{
			if (player->getScore() > 500) {
				enemies.push_back(Enemy{});
				enemies.push_back(Enemy{});

				addEnemy2 = false;
			}
		}

		if (player->getScore() > 2000 && addEnemy2 == false)
		{
			enemies.push_back(Enemy{});
			enemies.push_back(Enemy{});
			enemies.push_back(Enemy{});
			enemies.push_back(Enemy{});			
			addEnemy1 = false;

		}		
	}	

	// move the enemy towards the player
	for (auto& e : enemies) {
		
		e.rotation = atan2(playerRect->y - e.myRect.y, playerRect->x - e.myRect.x) * 180 / M_PI;

		if (player->getScore() < 1000)
		{
			if (e.myRect.x < playerX) {
				e.myRect.x++;
			}
			else e.myRect.x--;
			if (e.myRect.y < playerY) {
				e.myRect.y++;
			}
			else e.myRect.y--;
		}
		else if(player->getScore()<2000) {
			if (e.myRect.x < playerX) {
				e.myRect.x +=2;
			}
			else e.myRect.x-=2;
			if (e.myRect.y < playerY) {
				e.myRect.y+=2;
			}
			else e.myRect.y-=2;
		}
		else {
			if (e.myRect.x < playerX) {
				e.myRect.x += 3;
			}
			else e.myRect.x -= 3;
			if (e.myRect.y < playerY) {
				e.myRect.y += 3;
			}
			else e.myRect.y -= 3;
		}
		
		
	}
};



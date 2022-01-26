#include "Player.h"

Player::Player(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHight) {
	renderer = sdlRenderer;
	 windowWidth = _windowWidth ;
	 windowHeight = _windowHight ;	 
	 score = 0; 
}

void Player::init() {
	SDL_Surface* image = IMG_Load("assets/survivor-walk_1.png");
	if (image == NULL) {
		std::cout << "Cannot ld image %s ", SDL_GetError();
		return;
	}

	texture = SDL_CreateTextureFromSurface(renderer, image);
	playerText.push_back(SDL_CreateTextureFromSurface(renderer, image));

	SDL_FreeSurface(image);

	image = IMG_Load("assets/survivor-walk_0.png");
	if (image == NULL) {
		std::cout << "Cannot ld image %s ", SDL_GetError();
		return;
	}
	texture = SDL_CreateTextureFromSurface(renderer, image);
	playerText.push_back(texture);

	image = IMG_Load("assets/survivor.png");
	if (image == NULL) {
		std::cout << "Cannot ld image %s ", SDL_GetError();
		return;
	}

	texture = SDL_CreateTextureFromSurface(renderer, image);

	playerWidth = 40;
	playerHeight = 60;
	playerRect = { windowWidth/3,windowHeight/3,playerWidth,playerHeight };
	playerGun = { 60,60,40,40 };

	texture = SDL_CreateTextureFromSurface(renderer, image);

	// move to clear if animations 
	SDL_FreeSurface(image);
}

void Player::render() {	
	
	// Calculate the angle of mouse position which is used to set the rotation of the player
				
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Point playerSpin = {20, 30};
	SDL_Point legSpin = {18, 10};
		
	//SDL_RenderDrawLine(renderer, x + 30, y + 30, x + 30, y - 100);

	
	
	
	if (playerMoving == true)
	{
		pAnimation++;
		if (pAnimation >= 10)
			pAnimation = 1;

		playerGun.x = playerRect.x + 3;
		playerGun.y = playerRect.y + 20;

		SDL_RenderCopyEx(renderer, playerText[pAnimation / 5], NULL, &playerGun, angle, &legSpin, flip);
	}
		


		SDL_RenderCopyEx(renderer, texture, NULL, &playerRect, angle, &playerSpin, flip);

		PlayerHPBar(playerRect.x - 10, playerRect.y - 10, 60, 10, health, barRed, barBlue);
		playerMoving = false;

}

void Player::PlayerHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor) {
	Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	SDL_Color col;
	SDL_GetRenderDrawColor(renderer, &col.r, &col.g, &col.g, &col.a);
	SDL_Rect bgrect = { x, y, w, h };
	SDL_SetRenderDrawColor(renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	SDL_RenderFillRect(renderer, &bgrect);
	SDL_SetRenderDrawColor(renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	int pw = (int)((float)w * Percent);
	int px = x + (w - pw);
	SDL_Rect fgrect = { px, y, pw, h };
	SDL_RenderFillRect(renderer, &fgrect);
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
}


void Player::update()
{	
	angle = (atan2( mouseX - playerRect.x, playerRect.y - mouseY) * 180 / M_PI) ;
	//std::cout << angle << "angle" << std::endl;
		//playerGun = { };	
}


void Player::clean() {

}

bool Player::collision()
{
	//SDL_HasIntersection();
	return true;
}

void Player::moveRight() {
	
	if (playerRect.x + playerRect.w <= windowWidth)
	{
		std::cout << "player portion x " << playerRect.x << "window width " << windowWidth << std::endl;
		playerRect.x += speed;

		playerMoving = true;
	}	
}

void Player::moveLeft() {
		
	if (playerRect.x >= 0)
	{
		playerRect.x -= speed;
		//std::cout << "player portion x " << portion.x << "window width " << windowWidth << std::endl;

		playerMoving = true;
		
	}

}

void Player::moveUp() {
	if (playerRect.y >= 0 ) {
		playerRect.y -= speed;

		playerMoving = true;
	}
}

void Player::moveDown() {
	
	if (playerRect.y + playerHeight <= windowHeight) {
		playerRect.y += speed;

		playerMoving = true;
	}

}

double Player::getAngle()const
{
	return angle;
}

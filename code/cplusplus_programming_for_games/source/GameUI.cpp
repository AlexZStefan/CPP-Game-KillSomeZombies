#include "GameUI.h"

GameUI::GameUI(SDL_Renderer* renderer, int& screenWidth, int& screenHeight, FontRenderer* font) {
	this->renderer = renderer;
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	this->mainMenuFont = font;
};

void GameUI::init()
{			
	mainMenuPanel = { screenWidth/10, 0 ,500,screenHeight };
	
	startResumeButton = { screenWidth / 10 + 10, screenHeight / 4 ,480,100 };

	optionsButton = { screenWidth / 10+10, screenHeight / 4+110  ,480,100 };

	exitButton = { screenWidth / 10+10, screenHeight / 4 +220,480,100 };

	playerStats= { 0, 0,screenWidth,50 };

	loadScore();
}

Button::Button(int x, int y, int w, int h) {	
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	buttonRect = { x,y,w,h };	
	std::cout << std::endl << screenHeight << "buttonRect" << buttonRect.x << std::endl;
}

void Button::render(std::string txt, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	this->text = txt;

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &buttonRect);

	mainMenuFont->render(txt.c_str(),32, 123, 12, 123);
	SDL_RenderDrawRect(renderer, &buttonRect);
}

void GameUI::playerUI(int pScore, float pHp, bool gameOver)
{	
	auto sc = std::to_string(pScore);
	int hp = int(pHp * 100);
	
	auto php = std::to_string(hp);
		
	mainMenuFont->render("Score: " + sc, 0, 0, 100, 50);
	mainMenuFont->render("Health: " + php, 150, 0, 200, 50);
	mainMenuFont->render("Hi-score: " + playerHiScore, 400, 0, 200, 50);	
	
}

void GameUI::displayMenu()
{
	/*
	Button* exitButton = new Button(screenWidth/4, screenHeight/4 , 750,750);
	exitButton->render("Macaarr", 123,123,123,255);

	*/
	// renderer Menu Panel	
	SDL_SetRenderDrawColor(renderer, 59, 98, 253, 255);
	SDL_RenderFillRect(renderer, &mainMenuPanel);	
	mainMenuFont->render("KillSomeZombies", screenWidth / 10, 0 , 480, 100);
	SDL_RenderDrawRect(renderer, &mainMenuPanel);

	// renderer Start/Resume button		
	SDL_SetRenderDrawColor(renderer, 100, 172 - opColorChange, 255, 255);
	SDL_RenderFillRect(renderer, &startResumeButton);
	mainMenuFont->render("Start", startResumeButton.x, startResumeButton.y, startResumeButton.w, startResumeButton.h);
	SDL_RenderDrawRect(renderer, &startResumeButton);

	// renderer Option button		
	SDL_SetRenderDrawColor(renderer, 100, 172- opColorChange, 255, 255);
	SDL_RenderFillRect(renderer, &optionsButton);
	mainMenuFont->render("Options", optionsButton.x, optionsButton.y, optionsButton.w, optionsButton.h);
	SDL_RenderDrawRect(renderer, &optionsButton);

	// renderer Exit button		
	SDL_SetRenderDrawColor(renderer, 100, 172- exColorChange, 255, 255);
	SDL_RenderFillRect(renderer, &exitButton);
	mainMenuFont->render("Quit", exitButton.x+20, exitButton.y+20, exitButton.w-50, exitButton.h-50);
	SDL_RenderDrawRect(renderer, &exitButton);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	
}

void GameUI::GameOver()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect gameOverScreen = { 0,0,screenWidth,screenHeight };

	SDL_RenderFillRect(renderer, &gameOverScreen);
	mainMenuFont->render("You are zombie food", screenWidth / 10, 100, 480, 100);
	
	SDL_RenderFillRect(renderer, &exitButton);
	mainMenuFont->render("Quit", exitButton.x + 20, exitButton.y + 20, exitButton.w - 50, exitButton.h - 50);
	SDL_RenderDrawRect(renderer, &exitButton);	
}

void GameUI::loadScore()
{	
	std::fstream file("pScore.txt");	
	std::string input;	
	
	if (file.is_open())
	{
		std::getline(file, playerHiScore);
	}
	
	//playerHiScore= atoi(input.c_str());

	file.close();
}

void GameUI::saveScore(std::string score)
{	
	std::ofstream file("pScore.txt");

	file << score;
	//playerHiScore= atoi(input.c_str());

	file.close();
}





void GameUI::update()
{
	
}

void GameUI::clean()
{
	renderer = nullptr; 	
}

void GameUI::optionColorChange()
{
	opColorChange = 20;	
}

void GameUI::exitColorChange()
{
	exColorChange = 20;		
}



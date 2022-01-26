#pragma once

#include "FontRenderer.h"
#include <string>
#include <sdl.h>
#include <fstream>
#include <iostream>

class GameUI
{

public:
	GameUI() {};

	GameUI(SDL_Renderer* renderer, int& screenWidth, int& screenHeight, FontRenderer* font);
	void init();
	
	void playerUI(int pScore, float pHp, bool gameOver);
	void displayMenu();
	void GameOver();
	void loadScore();
	static void saveScore(std::string score);
	void update();
	void clean();
	void optionColorChange();
	void exitColorChange();

	SDL_Rect mainMenuPanel;
	SDL_Rect startResumeButton;
	SDL_Rect exitButton;
	SDL_Rect optionsButton;
	SDL_Rect playerStats;

protected:
	SDL_Renderer* renderer = nullptr;
	std::string playerHiScore;
	Uint8 opColorChange = 0;
	Uint8 exColorChange = 0;

	FontRenderer* mainMenuFont = nullptr;

	int screenHeight;
	int screenWidth;
};

class Button :public GameUI {

public:
	Button(int x, int y, int w, int h);
	void render(std::string txt, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

private:
	SDL_Rect buttonRect;
	SDL_Renderer* buttonRenderer;
	int x, y, w, h;
	std::string text;

};

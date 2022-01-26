#pragma once
#define SDL_MAIN_HANDLED
#include "GameLoop.h"

// exit game issue 
// buttons

int main(int argc, char** argv[]) {

	int c = 0;
	const int FPS = 10;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	GameLoop gameLoop = GameLoop();

	if (gameLoop.init() < 0) return -1;

	while (gameLoop.keepAlive())
	{
		frameStart = SDL_GetTicks();

		gameLoop.update();
		gameLoop.render();
		c++;

		// std::cout << c << std::endl;		// Frame Rate
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	};
	gameLoop.clean();

	return 0;
}


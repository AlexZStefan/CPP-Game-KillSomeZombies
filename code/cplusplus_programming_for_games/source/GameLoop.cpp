#include "GameLoop.h"

GameLoop::GameLoop()
{
	tileRct = NULL;
}

int GameLoop::init() {

	if (SDL_Init(SDL_INIT_VIDEO < 0)) {
		std::cout << "Could not initialize SDL Error: %s" << SDL_GetError();
		return -1;
	}

	window = SDL_CreateWindow("MyGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		std::cout << "Cannot initialize window %s " << SDL_GetError();
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "Cannot initialize renderer %s " << SDL_GetError();
		return -1;
	}

	screenSurface = SDL_GetWindowSurface(window);

	fontRenderer = new FontRenderer(renderer, screenWidth, screenHeight);
	fontRenderer->init();

	gameUI = std::unique_ptr<GameUI>(new GameUI(renderer, screenWidth, screenHeight, fontRenderer));
	gameUI->init();

	player = new Player(renderer, screenWidth, screenHeight);
	player->init();
	playerRct = &player->getRect();

	//myPlayer = std::unique_ptr<GameObject>(new GameObject("assets/chibiCarlo.png", renderer));
	//myPlayer = new GameObject("assets/chibiCarlo2.png" , renderer);

	tileMap = std::unique_ptr<TileMap>(new TileMap(renderer, "assets/tilemap/basechip_pipo.png", screenWidth, screenHeight, 0));
	tileMap->init();

	overTileMap = std::unique_ptr<TileMap>(new TileMap(renderer, "assets/tilemap/basechip_pipo.png", screenWidth, screenHeight, 1));
	overTileMap->init();

	// map tiles
	tilesNotWalkable = overTileMap->getTileRect(); 
	destroyableTiles = &overTileMap->getDamagableTileRect(); 
	tileRct = &tilesNotWalkable[0];

	bm = std::unique_ptr<BulletManager>(new BulletManager(renderer, player));
	bm->init();

	//handles enemy spawn
	em = std::unique_ptr<EnemyManager>(new EnemyManager(renderer, player));
	em->init();
	// handles coin spawn 
	collectables = std::unique_ptr<Collectables>(new Collectables(renderer));

	soundPlayer = new SoundPlayer();
	soundPlayer->PlaySound(4);

	gunFire = new GunFire("assets/sparks.png", renderer,0,0);
	
	particleSystem = new ParticleSystem(renderer);
	return 0;
};

void GameLoop::update() {

	if (!isGamePaused && gameStarted) {
			
		player->update();
		bm->update();
		em->update();
		collectables->update(player);
		playerRct = &player->getRect();
		
		std::vector <Bullet*> playerAmmo = bm->getAmmo();

		em->spawner();

		particleSystem->Update();
		
	/*	particleSystem->setRectPos(playerRct->x);
		particleSystem->setRectYPos(playerRct->y);*/

		tileMapCollision();

		//enemyCollision(*playerRct);
		bulletCollision(playerAmmo, *playerRct);
		//std::cout << Functions::getDistanceNotSqrt(bulletRect->x, bulletRect->y, enemyRect->x, enemyRect->y) << std::endl;		
	}
};


void GameLoop::render() {

	// set the renderer background color
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Game playing
	if (gameStarted && !isGamePaused && !gameOver) {
		tileMap->render();
		overTileMap->render();
		player->render();
		bm->draw();
		em->render();
		collectables->render();
		gameUI->playerUI(player->getScore(), player->getHealth(), gameOver);
		
		gunFire->render(player->getAngle(), renderer);

		particleSystem->Render(screenSurface);


		if (player->getHealth() <= 0)
		{
			gameOver = true;
			GameUI::saveScore(std::to_string(player->getScore()));

		}

	}

	// Game not started
	if (!gameStarted && isGamePaused && !gameOver) {
		gameUI->displayMenu();
	}

	// Game is paused
	if (isGamePaused && gameStarted && !gameOver) {
		fontRenderer->render("Pause", 100, 200, 100, 100);
		gameUI->displayMenu();
	}

	//std::cout << "isGamePaused" << isGamePaused << "gameStarted" << gameStarted << std::endl;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	if (gameOver)
	{
		gameStarted = false;
		isGamePaused = true;
		gameUI->GameOver();
	}

	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
};

void GameLoop::clean() {
	SDL_FreeSurface(screenSurface);
	SDL_DestroyWindow(window);
	gameUI->clean();
	bm->clean();
	delete player;
	player = nullptr;

	em->clean();
	fontRenderer->clean();
	tileMap->clean();
	overTileMap->clean();

	delete fontRenderer;
	fontRenderer = nullptr;

	destroyableTiles->clear();

	tilesNotWalkable.clear();

	screenSurface = nullptr;

	gunFire->clean();
	gunFire = nullptr;

	delete particleSystem;
	particleSystem = nullptr;


	delete soundPlayer;
	soundPlayer = nullptr;
	SDL_Quit();
};


void GameLoop::bulletCollision(std::vector <Bullet*> playerAmmo, SDL_Rect& playerRct)
{
	for (auto& e : collectables->getCollectables())
	{
		if (Functions::myCollision(e.objectRect(), playerRct))
		{
			soundPlayer->PlaySound(0);
			e.setRenderStatus(false);
			e.setRectPos(-50);	
			player->setScore(100);
		}
	}
	
	for (auto& e : em->getEnemies())
	{
		if (Functions::collision(playerRct, e.myRect))
		{
			// stop rendering the enemy if colided and change it`s position
			e.render = false;
			player->setHp(0.25f);		
		}

		if (e.render == true)
		{
			for (auto& a : playerAmmo)
			{
				if (a->render == true) {

					// circle collision
					if (Functions::circleCollision(a->bulletRect.x, a->bulletRect.y, a->radius, e.myRect))
					{
						e.render = false;
						a->render = false;
						soundPlayer->PlaySound(1+rand() % 2);
						collectables->spawn(e.myRect);
						player->setScore(10);
					}

					// rectangle collision
					/*if (Functions::myCollision(a->bulletRect, e.myRect))
					{						
					}*/

					for (auto& dt : *destroyableTiles)
					{
						if (Functions::collision(a->bulletRect, dt.tile))
						{
							std::cout << " Collision with rock" << std::endl;
							dt.render == false;

							//swap the tiles if collision happens
							overTileMap->mapOver[dt.yPos][dt.xPos] = 64;							
						}
					}
				}
			}
		}
	}
}

void GameLoop::tileMapCollision()
{
	for (auto& t : tilesNotWalkable) {
		playerRct = &player->getRect();

		if (Functions::myCollision(t, *playerRct))
		{
			tileRct = &t;
			std::cout << "t.x " << t.x << std::endl;

			// coll up 
			if (playerRct->y + playerRct->h > tileRct->y + tileRct->h)
			{
				playerRct->y += 5;
			}
			// coll left 
			if (playerRct->x + playerRct->w > tileRct->x + tileRct->w)
			{
				playerRct->x += 5;
			}
			//coll right 
			if (playerRct->x + playerRct->w < tileRct->x + tileRct->w)
			{
				playerRct->x -= 5;
			}
			//coll down
			if (playerRct->y + playerRct->h < tileRct->y + tileRct->h)
			{
				playerRct->y -= 5;
			}
		}
		if (tileRct != nullptr)
		{
			if (!(Functions::myCollision(*tileRct, *playerRct)))
			{
				tileRct = nullptr;
			}
		}
	}
}

void GameLoop::pauseGame() {
	if (isGamePaused) {
		if ((player->mouseX > gameUI->startResumeButton.x) &&
			(player->mouseX < gameUI->startResumeButton.x + gameUI->startResumeButton.w))
		{
			if ((player->mouseY > gameUI->startResumeButton.y) &&
				(player->mouseY < gameUI->startResumeButton.y + gameUI->startResumeButton.h))
			{
				gameStarted = true;
				isGamePaused = false;
				gameUI->exitColorChange();
			}

			if ((player->mouseY > gameUI->exitButton.y) &&
				(player->mouseY < gameUI->exitButton.y + gameUI->exitButton.h))
			{
				gameStarted = false;
				isGamePaused = false;
				gameUI->exitColorChange();
				
				quitTheGame = true;
			}

			//std::cout << "exitButton Clicked" << std::endl;
			if ((player->mouseY > gameUI->optionsButton.y) &&
				(player->mouseY < gameUI->optionsButton.y + gameUI->optionsButton.h))
				gameUI->optionColorChange();
			//std::cout << "optionsButton Clicked" << std::endl;
		}
	}
	SDL_Delay(500);
}

void GameLoop::handleInput(SDL_Scancode& keyScanCode, SDL_Event& event) {
	switch (keyScanCode)
	{
	case SDLK_ESCAPE:
		isGamePaused = (isGamePaused == true) ? false : true;
		break;
	default:
		break;
	}
	if (!isGamePaused) {
	switch (keyScanCode) {
		
	case SDL_SCANCODE_D:
		if (tileRct != nullptr)
		{
			//collision check for tiles not walkable 
			if (playerRct->x + playerRct->w < tileRct->x)
			{
				player->moveRight();
			}
		}
		else if (tileRct == nullptr)
			player->moveRight();


		break;
	case SDL_SCANCODE_A:
		if (tileRct != nullptr)
		{
			if (playerRct->x > tileRct->x + tileRct->w)
				player->moveLeft();
		}
		else if (tileRct == nullptr)
			player->moveLeft();

		break;
	case SDL_SCANCODE_W:
		if (tileRct != nullptr)
		{
			if (playerRct->y > tileRct->y + tileRct->h)
			{
				player->moveUp();
			}
		}
		else if (tileRct == nullptr)
			player->moveUp();

		break;
	case SDL_SCANCODE_S:
		if (tileRct != nullptr)
		{
			if (playerRct->y + playerRct->h < tileRct->y)
				player->moveDown();
		}
		else if (tileRct == nullptr)
			player->moveDown();
		break;
	}
	}
	switch (event.button.button) {
	case SDL_BUTTON_LEFT: {
		if (SDL_MOUSEBUTTONDOWN) {
			
			if (isGamePaused) {
				pauseGame();
			}
			if (!gameOver)
			{
				quitGame();
			}
		}
		break;
	}
	case SDL_BUTTON_RIGHT:
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (!isGamePaused && gameStarted)
			{
				bm->shoot();
				soundPlayer->PlaySound(3);

				gunFire->update(playerRct->x, playerRct->y);
				gunFire->setRender(true);
				
			}			
		}
	default:
		break;
	}
}

bool GameLoop::keepAlive() {
	SDL_Event userInput;

	// use for keydown only
	const Uint8* state = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&userInput)) {

		if (userInput.type == SDL_QUIT)
		{
			return false;
		}

		// might throw error( if screen VS freezes)
		if (userInput.type == SDL_KEYDOWN || userInput.button.button) {
			handleInput(userInput.key.keysym.scancode, userInput);
		}

		// Pause Game 
		if (state[SDL_SCANCODE_ESCAPE])
		{
			isGamePaused = (isGamePaused == true) ? false : true;
			SDL_Delay(100);
		}

		// Handle Mouse Input
		if (userInput.type == SDL_MOUSEMOTION) {
			// captures and set the mouse x and y position
			SDL_GetMouseState(&(player->mouseX), &(player->mouseY));
		}
	}
	if(quitTheGame == true)
	{
		return false;
	}

	return true;
}

SDL_bool GameLoop::collision(SDL_Rect& value, SDL_Rect& rect2) {
	return SDL_HasIntersection(&value, &rect2);
}
//std::queue<int>* mAvailableEntities = new std::queue<int>;

void GameLoop::quitGame()
{
	if ((player->mouseX > gameUI->exitButton.x) &&
		(player->mouseX < gameUI->exitButton.x + gameUI->exitButton.w))
		if ((player->mouseY > gameUI->exitButton.y) &&
			(player->mouseY < gameUI->exitButton.y + gameUI->exitButton.h))
		{			
			quitTheGame = true;
		}
}
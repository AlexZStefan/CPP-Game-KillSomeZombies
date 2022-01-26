#include "Collectables.h"

Collectables::Collectables(SDL_Renderer* rend)
{
	x = 10;
	y= 10;

	value = 10;
	health = 10;

	for (int i = 0; i < 10; i++) {
		coin.push_back(GameObject("assets/collectables/ItemPack/HeavyOutline/S_ItemHeavyOutline_CoinGold_00.png", rend, -5,0));		
	}	
}

void Collectables::spawn(SDL_Rect& enemyRect)
{
	
	if ( spawnItem == 9) spawnItem = 0;
	coin[spawnItem].xPos = enemyRect.x;
	coin[spawnItem].yPos = enemyRect.y;
	coin[spawnItem].setRenderStatus(true);
	spawnItem++;
}

void Collectables::clean()
{
	coin.clear();
}

void Collectables::render()
{
	for (std::vector<GameObject>::iterator item = coin.begin(); item != coin.end(); ++item) {	
		item->render();		
	}
}

void Collectables::update(Player* player)
{	
	for (auto& item : coin)
	{			
		item.update();		
	};
}

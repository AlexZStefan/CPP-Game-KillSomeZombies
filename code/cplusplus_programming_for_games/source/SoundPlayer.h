#pragma once

#include <vector>
#include <sstream>
#include <SDL_mixer.h>

enum Sounds {
	CoinCollect,
	ZombieAttack,
	ZombieDeath, 
	PlayerShoot,
	GameMusic,
	TOTAL_SOUNDS
};

class SoundPlayer {
public:
	SoundPlayer();
	virtual ~SoundPlayer();
	void PlaySound(int sound);

private:
	Mix_Music* musicPlayer;
	std::vector<Mix_Chunk*> soundFiles;
};
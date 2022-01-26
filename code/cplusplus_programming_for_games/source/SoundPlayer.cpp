#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
	{
		std::printf("AudioMixer could not be created! SDL_Error : %s\n", SDL_GetError());
	}
	for (int i = 0; i < TOTAL_SOUNDS; i++)
	{
		std::stringstream name;
		name << "assets/sounds/";
		name<< i;
		name << ".wav";
		Mix_Chunk* sound = Mix_LoadWAV(name.str().c_str());
		soundFiles.push_back(sound);		
	}
}

SoundPlayer::~SoundPlayer()
{
	for (auto& sound : soundFiles) {
		Mix_FreeChunk(sound);
	}
	Mix_FreeMusic(musicPlayer);
}

void SoundPlayer::PlaySound(int sound)
{
	Mix_PlayChannel(-1, soundFiles[sound], 0);	
}

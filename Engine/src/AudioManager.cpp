#include "AudioManager.h"

//The audio manager plays music or an SFX

AudioManager* AudioManager::Istance = nullptr;

AudioManager* AudioManager::GetIstance() {
	//This class is a singleton
	if (Istance == nullptr) {
		Istance = new AudioManager();
	}
	return Istance;
}

void AudioManager::Clear() {
	delete Istance;
	Istance = nullptr;
}

AudioManager::AudioManager() {
	resourceManager = ResourceManager::GetIstance();

	//We initialize the library
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		std::cout << "Mixer Initalization error " << Mix_GetError() << std::endl;
	}
}

AudioManager::~AudioManager() {
	resourceManager = nullptr;
	Mix_Quit();
}

//Functions to play music or an sfx, to pause/stop music and to set the music volume
void AudioManager::PlayMusic(std::string filepath, int loops) {
	Mix_PlayMusic(resourceManager->TakeMusic(filepath), loops);
}

void AudioManager::PauseMusic() {
	if (Mix_PlayingMusic != 0) {
		Mix_PauseMusic();
	}
}

void AudioManager::ResumeMusic() {
	if (Mix_PausedMusic != 0) {
		Mix_ResumeMusic();
	}
}

void AudioManager::SetVolumeMusic(int volume) {
	Mix_VolumeMusic(volume);
}

void AudioManager::PlaySFX(std::string filepath, int loops, int channel) {
	Mix_PlayChannel(channel, resourceManager->TakeSFX(filepath), loops);
}
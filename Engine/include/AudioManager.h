#pragma once
#include "ResourceManager.h"

class AudioManager {
private:
	static AudioManager* Istance;
	ResourceManager* resourceManager;
public:
	static AudioManager* GetIstance();
	static void Clear();

	void PlayMusic(std::string filepath, int loops = -1);
	void PauseMusic();
	void ResumeMusic();
	void SetVolumeMusic(int volume);

	void PlaySFX(std::string filepath, int loops = 0, int channel = 0);

private:
	AudioManager();
	~AudioManager();
};
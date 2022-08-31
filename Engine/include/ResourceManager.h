#pragma once

#include <iostream>
#include <map>
#include <string>
#include <SDL_mixer.h>
#include "SDL_ttf.h"
#include "Graphics.h"

class ResourceManager {
private:
	static ResourceManager* Instance;
	GraphicsManager* graphicsManager;

	std::map<const char*, SDL_Texture*> TextureMap;
	std::map<std::string, TTF_Font*> FontsMap;
	std::map<std::string, Mix_Music*> MusicMap;
	std::map<std::string, Mix_Chunk*> SFXMap;

public:
	static ResourceManager* GetIstance();

	SDL_Texture* TakeTexture(const char* filepath);
	TTF_Font* TakeFont(std::string filepath, int size);
	Mix_Music* TakeMusic(std::string filepath);
	Mix_Chunk* TakeSFX(std::string filepath);
	
	static void Clear();
private:
	ResourceManager();
	~ResourceManager();

	TTF_Font* CreateFont(std::string filepath, int fontsize);
};
#pragma once

#include <iostream>
#include <map>
#include <string>
#include "SDL_ttf.h"
#include "Graphics.h"

class ResourceManager {
private:
	static ResourceManager* Instance;
	GraphicsManager* graphicsManager;

	std::map<const char*, SDL_Texture*> TextureMap;
	std::map<std::string, TTF_Font*> fonts;

public:
	static ResourceManager* GetIstance();

	SDL_Texture* TakeTexture(const char* filepath);
	TTF_Font* TakeFont(std::string filepath, int size);
	
	void Clear();
private:
	ResourceManager();
	~ResourceManager();

	TTF_Font* CreateFont(std::string filepath, int fontsize);
};
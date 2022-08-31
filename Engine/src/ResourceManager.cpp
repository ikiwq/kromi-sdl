#include "ResourceManager.h"

//The resource manager is intended to optimize resources and time.
//Ex: an audio or an image is loaded as new every time it needs to.

ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager* ResourceManager::GetIstance() {
	//This class is a singleton
	if (Instance == nullptr) {
		Instance = new ResourceManager();
	}
	return Instance;
}

ResourceManager::ResourceManager() {
	graphicsManager = GraphicsManager::GetIstance();
}

ResourceManager::~ResourceManager() {
	TextureMap.clear();
	FontsMap.clear();
	MusicMap.clear();
	SFXMap.clear();
	graphicsManager = nullptr;
}

void ResourceManager::Clear() {
	delete Instance;
	Instance = nullptr;
}

//We can associate an asset with his filepath in a map.
SDL_Texture* ResourceManager::TakeTexture(const char* filepath) {
	//If the filepath points to an asset in the map, then it will return the asset.
	if (TextureMap.count(filepath)) {
		auto it = TextureMap.find(filepath);
		return it->second;
	}
	//otherwise, the asset will be loaded into the map.
	else {
		SDL_Texture* txtr = graphicsManager->GetTexture(filepath);
		TextureMap.emplace(filepath, txtr);
		return txtr;
	}
}

//The same procedure applies to all the other assets.

TTF_Font* ResourceManager::TakeFont(std::string filepath, int size) {
	std::string intg = std::to_string(size);
	std::string id = filepath + intg;
	if (FontsMap.count(id)) {
		auto it = FontsMap.find(id);
		return it->second;
	}
	else {
		TTF_Font* font = CreateFont(filepath, size);
		FontsMap.emplace(id, font);
		return font;
	}
}

TTF_Font* ResourceManager::CreateFont(std::string filepath, int fontsize) {
	return TTF_OpenFont(filepath.c_str(), fontsize);
}

Mix_Music* ResourceManager::TakeMusic(std::string filepath) {
	if (MusicMap.count(filepath)) {
		auto it = MusicMap.find(filepath);
		return it->second;
	}
	else {
		Mix_Music* Music = Mix_LoadMUS(filepath.c_str());
		MusicMap.emplace(filepath, Music);
		return Music;
	}
}

Mix_Chunk* ResourceManager::TakeSFX(std::string filepath) {
	if (SFXMap.count(filepath)) {
		auto it = SFXMap.find(filepath);
		return it->second;
	}
	else {
		Mix_Chunk* SFX = Mix_LoadWAV(filepath.c_str());
		SFXMap.emplace(filepath, SFX);
		return SFX;
	}
}
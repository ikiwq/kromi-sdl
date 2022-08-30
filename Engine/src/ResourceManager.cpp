#include "ResourceManager.h"

ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager* ResourceManager::GetIstance() {
	if (Instance == nullptr) {
		Instance = new ResourceManager();
	}
	return Instance;
}

ResourceManager::ResourceManager() {
	graphicsManager = GraphicsManager::GetIstance();
}

ResourceManager::~ResourceManager() {
	Clear();
}

void ResourceManager::Clear() {
	TextureMap.clear();
	graphicsManager = nullptr;
	delete Instance;
	Instance = nullptr;
}

SDL_Texture* ResourceManager::TakeTexture(const char* filepath) {
	if (TextureMap.count(filepath)) {
		auto it = TextureMap.find(filepath);
		return it->second;
	}
	else {
		SDL_Texture* txtr = graphicsManager->GetTexture(filepath);
		TextureMap.emplace(filepath, txtr);
		return txtr;
	}
}

TTF_Font* ResourceManager::TakeFont(std::string filepath, int size) {
	std::string intg = std::to_string(size);
	std::string id = filepath + intg;
	if (fonts.count(id)) {
		auto it = fonts.find(id);
		return it->second;
	}
	else {
		TTF_Font* font = CreateFont(filepath, size);
		fonts.emplace(id, font);
		return font;
	}
}

TTF_Font* ResourceManager::CreateFont(std::string filepath, int fontsize) {
	return TTF_OpenFont(filepath.c_str(), fontsize);
}

#include "Graphics.h"

GraphicsManager* GraphicsManager::Instance = nullptr;
bool GraphicsManager::isInitialized = false;

GraphicsManager* GraphicsManager::GetIstance() {
	if (Instance == nullptr) {
		Instance = new GraphicsManager();
	}
	return Instance;
}

GraphicsManager::GraphicsManager() {
	isInitialized = Init();
}

GraphicsManager::~GraphicsManager() {
}

void GraphicsManager::Clear() {
	delete Instance;
	Instance = nullptr;

	isInitialized = false;
}

SDL_Window* GraphicsManager::GetWindow() {
	return mWindow;
}

SDL_Renderer* GraphicsManager::GetRenderer() {
	return mRenderer;
}

bool GraphicsManager::isInit() {
	return isInitialized;
}

bool GraphicsManager::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL INITAILIZATION ERROR:\n" << SDL_GetError() << std::endl;
		return false;
	}
	if (TTF_Init() < 0) {
		std::cout << "SDL FONT INITALIZATION ERROR:\n" << SDL_GetError() << std::endl;
	}
	mWindow = SDL_CreateWindow("Kromi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, VideoX, VideoY, SDL_WINDOW_SHOWN);

	if (mWindow == NULL) {
		std::cout << "SDL WINDOW ERROR:\n" << SDL_GetError() << std::endl;
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == NULL) {
		std::cout << "SDL RENDERER ERROR:\n" << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

SDL_Texture* GraphicsManager::GetTexture(const char* filepath) {
	SDL_Surface* TextureSurface = IMG_Load(filepath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, TextureSurface);
	SDL_FreeSurface(TextureSurface);
	return texture;
}

void GraphicsManager::Render() {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(mRenderer);
	SDL_RenderClear(mRenderer);
}
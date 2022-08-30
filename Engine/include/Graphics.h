#pragma once

#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_ttf.h"
#include <iostream>

class GraphicsManager {
public:
	static const int VideoX = 1280;
	static const int VideoY = 720;
	const char* Title = "Kromi";

private:
	static GraphicsManager* Instance;
	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;

	static bool isInitialized;

public:
	bool isInit();

	static GraphicsManager* GetIstance();
	static void Clear();

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();

	SDL_Texture* GetTexture(const char* filepath);

	void Render();

private:
	GraphicsManager();
	~GraphicsManager();

	bool Init();
};
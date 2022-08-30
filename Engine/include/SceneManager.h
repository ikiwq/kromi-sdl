#pragma once
#include "Graphics.h"
#include "Timer.h"

class Game;
class MainMenu;

class SceneManager {
private:
	static SceneManager* Istance;
	
	GraphicsManager* graphicsManager;
	Timer* timer;

	Game* game;
	MainMenu* mainMenu;

	bool ShouldQuit;
public:
	static SceneManager* GetIstance();

	void Run();
	static void Clear();
private:
	SceneManager();
	~SceneManager();
};
#pragma once
#include "SDL.h"
#include "ResourceManager.h"
#include "AudioManager.h"

class EntityManager;
class Map;

class Scene {
public:
	EntityManager* entityManager;
	GraphicsManager* graphics;
	ResourceManager* resourceManager;
	AudioManager* audioManager;

	SDL_Rect Camera;
	SDL_Event Event;


	Map* map;
	int SceneSizeX, SceneSizeY;

	bool ShouldQuit;
	bool isPaused;
	bool isActive;

	Scene();
	~Scene() {
		graphics = nullptr;
		resourceManager = nullptr;
		delete entityManager;
		entityManager = nullptr;
		delete map;
		map = nullptr;
	}

	bool Init() {}

	virtual void Update() {}

	virtual void Render() {}

};
#pragma once
#include "SDL.h"
#include "ResourceManager.h"

class EntityManager;
class Map;

class Scene {
public:
	EntityManager* entityManager;
	SDL_Rect Camera;
	GraphicsManager* graphics;
	ResourceManager* resourceManager;
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
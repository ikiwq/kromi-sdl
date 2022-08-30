#include "Scene.h"
#include "ECS.h"
#include "Map.h"

Scene::Scene():ShouldQuit(false), isPaused(false), isActive(true) {
	entityManager = new EntityManager();
	graphics = GraphicsManager::GetIstance();
	resourceManager = ResourceManager::GetIstance();
	map = new Map();
	Camera = { 0,0, graphics->VideoX, graphics->VideoY };
	entityManager->ManagerScene = this;
}

#include "Scene.h"

#include "ECS.h"
#include "Map.h"

//Every scene will inherit from the Scene class.
//Each class can be paused/active. This can be useful in the scene manager to switch scenes.
//Every class has a some base components shown in the Scene.h file.
//The Sprite and Transfrom component take the Camera in their Entity Scene
//for calculations.

Scene::Scene():ShouldQuit(false), isPaused(false), isActive(true) {
	entityManager = new EntityManager();
	graphics = GraphicsManager::GetIstance();
	resourceManager = ResourceManager::GetIstance();
	audioManager = AudioManager::GetIstance();

	map = new Map();
	Camera = { 0,0, graphics->VideoX, graphics->VideoY };
	entityManager->ManagerScene = this;
}

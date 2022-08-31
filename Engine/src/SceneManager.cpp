#include "Game.h"
#include "MainMenu.h"
#include "SceneManager.h"

//The scene manager Updates and Render Scenes and manages the exit conditions.

SceneManager* SceneManager::Istance = nullptr;

SceneManager* SceneManager::GetIstance() {
	//This class is a singleton
	if (Istance == nullptr) {
		Istance = new SceneManager();
	}
	return Istance;
}

SceneManager::SceneManager(): ShouldQuit(false) {
	graphicsManager = GraphicsManager::GetIstance();
	timer = Timer::GetInstance();

	//Create the scenes
	game = new Game(2560, 2560);
	mainMenu = new MainMenu(1280, 720);
}

SceneManager::~SceneManager() {
	delete game;
	game = nullptr;
	delete mainMenu;
	mainMenu = nullptr;
}

void SceneManager::Clear() {
	delete Istance;
}

void SceneManager::Run() {
	//Exit conditions
	while (game->ShouldQuit == false && mainMenu->ShouldQuit == false) {

		//Update the render timer and the physics timer
		timer->UpdatePhysics();
		timer->Update();

		//If the dT between each update is more than 1/Calls per seconds, do an Update
		if (timer->GetPhysicsDt() > 1 / timer->PhysicsCallPerSeconds) {

			//Update stuff
			if (mainMenu->isActive) {
				mainMenu->Update();
			}
			else {
				game->Update();
			}

			//The timer is reset once the update is completed
			timer->ResetPhysics();
		}

		//If the dT between each render is more than 1/Framerate, do a Render
		if (timer->GetDt() > 1 / timer->FPS) {

			//Render stuff
			if (mainMenu->isActive) {
				mainMenu->Render();
			}
			else {
				game->Render();
			}
			
			//The timer is reset and the render is presented
			timer->Reset();
			graphicsManager->Render();
		}
		
	}
}
#include "Game.h"
#include "MainMenu.h"
#include "SceneManager.h"

SceneManager* SceneManager::Istance = nullptr;

SceneManager* SceneManager::GetIstance() {
	if (Istance == nullptr) {
		Istance = new SceneManager();
	}
	return Istance;
}

SceneManager::SceneManager(): ShouldQuit(false) {
	graphicsManager = GraphicsManager::GetIstance();
	timer = Timer::GetInstance();

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
	while (!ShouldQuit) {
		if (game->ShouldQuit == true || mainMenu->ShouldQuit == true) {
			ShouldQuit = true;
		}

		timer->UpdatePhysics();
		timer->Update();

		if (timer->GetPhysicsDt() > 1 / timer->PhysicsCallPerSeconds) {

			if (mainMenu->isActive) {
				mainMenu->Update();
			}
			else {
				game->Update();
				std::cout << "update!";
			}

			timer->ResetPhysics();
		}

		if (timer->GetDt() > 1 / timer->FPS) {

			if (mainMenu->isActive) {
				mainMenu->Render();
			}
			else {
				game->Render();
			}
			

			timer->Reset();
			graphicsManager->Render();
		}
		
	}
}
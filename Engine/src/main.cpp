#include "SDL.h"
#include "SceneManager.h"

int main(int argc, char* argv[]) {
	SceneManager* sceneManager = SceneManager::GetIstance();

	sceneManager->Run();

	sceneManager->Clear();
	return 0;
}
#pragma once
#include "Scene.h"
#include "Components.h"
#include "Collisions.h"
#include "MenuScript.h"

class MainMenu : public Scene {
public:
	Entity& ScriptContainer = entityManager->addEntity();
	Entity& Background = entityManager->addEntity();
	Entity& TitleScreen = entityManager->addEntity();
	Entity& Button1 = entityManager->addEntity();
	Entity& Button2 = entityManager->addEntity();

	MainMenu(int Scenex, int Sceney) {
		SDL_Color SDL_White = { 255,255,255,255 };

		SceneSizeX = Scenex;
		SceneSizeY = Sceney;

		ScriptContainer.addComponent<InputComponent>();
		ScriptContainer.addComponent<MenuScript>(this);
		ScriptContainer.AddGroup(zerolayer);

		Background.addComponent<Transform2D>(0, 0);
		Background.addComponent<FixedSpriteComponent>("assets/Background.png", 2000, 1000);
		Background.AddGroup(zerolayer);

		TitleScreen.addComponent<Transform2D>(670, 100);
		TitleScreen.addComponent<FixedSpriteComponent>(0, 0, 50, 50, 50);
		TitleScreen.addComponent<TextComponent>("KROMI ENGINE", "assets/Fonts/PressStart2P.ttf", 40,
			SDL_White, true);
		TitleScreen.AddGroup(firstlayer);
		
		Button1.addComponent<Transform2D>(515, 300);
		Button1.addComponent<FixedSpriteComponent>(300, 75, 50, 50, 50);
		Button1.addComponent<TextComponent>("PLAY", "assets/Fonts/PressStart2P.ttf", 20,
			SDL_White, true);
		Button1.AddGroup(firstlayer);

		Button2.addComponent<Transform2D>(515, 450);
		Button2.addComponent<FixedSpriteComponent>(300, 75, 50, 50, 50);
		Button2.addComponent<TextComponent>("QUIT", "assets/Fonts/PressStart2P.ttf", 20,
			SDL_White, true);
		Button2.AddGroup(firstlayer);

		Camera.x = 0;
		Camera.y = 0;
		Camera.w = graphics->VideoX;
		Camera.h = graphics->VideoY;

		//audioManager->PlayMusic("assets/Audio/MainMenu.wav");
		//audioManager->SetVolumeMusic(5);
		
	};
	~MainMenu() = default;

	void Update() {

		while (SDL_PollEvent(&Event) != 0) {
			if (Event.type == SDL_QUIT) {
				ShouldQuit = true;
			}
		}

		entityManager->Update();
		entityManager->Refresh();
	}

	void Render() {
		entityManager->Render();
	}
};
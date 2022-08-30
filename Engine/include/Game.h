#pragma once
#include "Scene.h"
#include "Map.h"
#include "ECS.h"

#include "Transform2D.h"
#include "FixedSpriteComponent.h"
#include "AnimationComponent.h"
#include "BoxCollider.h"
#include "InputComponent.h"
#include "PlayerScript.h"
#include "EnemyScript.h"
#include "TextComponent.h"

class Game : public Scene {
public:
	Entity& player = entityManager->addEntity();
	Entity& enemy = entityManager->addEntity();

	Game(int sizex, int sizey) {
		SceneSizeX = sizex;
		SceneSizeY = sizey;
		
		map->SetScene(this);
		map->LoadMap("assets/TileMap/TileSet1.png", "assets/TileMap/Map1.txt", 32, 80, 80);

		player.addComponent<Transform2D>(50, 50);
		player.addComponent<FixedSpriteComponent>("assets/Player1.png", 32, 32);
		player.addComponent<AnimationComponent>(32, 32, 10, 0.1);
		player.addComponent<BoxCollider>("player");
		player.addComponent<InputComponent>();
		player.addComponent<PlayerScript>();
		player.AddGroup(firstlayer);

		enemy.addComponent<Transform2D>(80, 80);
		enemy.addComponent<FixedSpriteComponent>("assets/Player1.png", 32, 32);
		enemy.addComponent<AnimationComponent>(32, 32, 10, 0.25);
		enemy.addComponent<BoxCollider>("enemy");
		enemy.addComponent<InputComponent>();
		enemy.addComponent<EnemyScript>();
		enemy.AddGroup(firstlayer);

		Camera.x = 0;
		Camera.y = 0;
		Camera.w = graphics->VideoX;
		Camera.h = graphics->VideoY;

	}

	~Game() = default;

	void Update(){

		while (SDL_PollEvent(&Event) != 0 ) {
			if (Event.type == SDL_QUIT) {
				ShouldQuit = true;
			}
		}

		entityManager->Update();
		entityManager->Refresh();
	}

	void Render(){
		entityManager->Render();
	}
};
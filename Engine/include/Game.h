#pragma once
#include "Scene.h"
#include "Map.h"
#include "ECS.h"

#include "Collisions.h"

#include "Components.h"


class Game : public Scene {
public:
	Entity& player = entityManager->addEntity();
	Entity& enemy = entityManager->addEntity();

	Game(int sizex, int sizey) {
		SceneSizeX = sizex;
		SceneSizeY = sizey;
		
		map->SetScene(this);
		map->LoadMap("assets/TileMap/TileSet1.png", "assets/TileMap/Map1.txt", 32, 80, 80);
		map->LoadDetailMap("assets/TileMap/TileSet1.png", "assets/TileMap/DetailMap1.txt", 32, 80, 80, 0);
		map->LoadCollisionMap("assets/TileMap/TileSet1.png", "assets/TileMap/CollisionMap1.txt", 32, 80, 80, 0);	
		
		player.addComponent<Transform2D>(50, 50);
		player.addComponent<FixedSpriteComponent>("assets/Player1.png", 32, 32);
		player.addComponent<AnimationComponent>(32, 32, 10, 0.1);
		player.addComponent<BoxCollider>("player");
		player.getComponent<BoxCollider>().showHitbox = true;
		player.addComponent<InputComponent>();
		player.addComponent<PlayerScript>();
		player.AddGroup(thirdlayer);

		enemy.addComponent<Transform2D>(100, 100);
		enemy.addComponent<FixedSpriteComponent>("assets/Player1.png", 32, 32);
		enemy.addComponent<AnimationComponent>(32, 32, 10, 0.25);
		enemy.addComponent<BoxCollider>("enemy");
		enemy.getComponent<BoxCollider>().showHitbox = true;
		enemy.addComponent<InputComponent>();
		enemy.addComponent<EnemyScript>();
		enemy.AddGroup(thirdlayer);

		Camera.x = player.getComponent<Transform2D>().GetPosition().x - Camera.w / 2;
		Camera.y = player.getComponent<Transform2D>().GetPosition().y - Camera.h / 2;
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

		//Update camera
		Camera.x = player.getComponent<Transform2D>().GetPosition().x - Camera.w/2;
		Camera.y = player.getComponent<Transform2D>().GetPosition().y - Camera.h/2;

		//Check for collisions
		for (int i = 0; i < entityManager->groupEntities[2].size(); i++) {
			for (int j = 0; j < entityManager->groupEntities[3].size(); j++) {
				if (Collisions::AxisCollision(entityManager->groupEntities[2][i]->getComponent<BoxCollider>(),
					entityManager->groupEntities[3][j]->getComponent<BoxCollider>())) {
					entityManager->groupEntities[3][j]->getComponent<BoxCollider>().isColliding = true;
				}
			}
		}

		entityManager->Update();
		entityManager->Refresh();
	}

	void Render(){
		entityManager->Render();
	}
};
#pragma once

#include <vector>
#include <fstream>
#include "ECS.h"

class Scene;
class Transform2D;
class FixedSpriteComponent;

class Map {
public:
	int MapW, MapH;
private:
	std::vector<Entity*> Tiles;
	Scene* scene;
public:
	Map();
	~Map();

	void LoadMap(const char* TextureFilepath, const char* TxtFilepath, int TileSize, int tilesX, int tilesY);

	void LoadCollisionMap(const char* TextureFilepath, const char* TxtFilepath) {

	}

	void SetScene(Scene* scene_);

};
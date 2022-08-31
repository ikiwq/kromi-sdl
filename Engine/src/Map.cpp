#include "Map.h"
#include "Scene.h"
#include "Transform2D.h"
#include "FixedSpriteComponent.h"
#include <BoxCollider.h>

//The map.h creates entities and assign them a sprite using a tile map and a sprite sheet.

Map::Map() {

}

Map::~Map() {
	Tiles.clear();
	scene = nullptr;
}

//The LoadMap function takes in a .txt with the tile map
void Map::LoadMap(const char* TextureFilepath, const char* TxtFilepath, int TileSize, int tilesX, int tilesY) {
	//tile is the integer that we are searching through the .txt file
	int tile;
	std::fstream mapTxt;

	//we retrieve the texture using the resource manager
	SDL_Texture* text = scene->resourceManager->TakeTexture(TextureFilepath);

	int TextureW, TextureH;
	SDL_QueryTexture(text, NULL, NULL, &TextureW, &TextureH);
	//The number of the tiles on each axis in the tile set is given by dividing the texture size by the tile size.
	int TileSetX = (TextureW / TileSize);
	int TileSetY = (TextureH / TileSize);

	mapTxt.open(TxtFilepath);

	//The tile map is a matrix. The matrix is configured as matrix[tiles on the Y axis] [tiles on the X axis]
	for (int y = 0; y < tilesY; y++) {
		for (int x = 0; x < tilesX; x++) {

			mapTxt >> tile;

			//those are the coordinates of the source rectangle(later will be multiplied by the tile size)
			int srcxpos = tile;
			int srcypos = 0;
			//we check that the position on the X axis does not exceed the tileset dimension
			while (srcxpos > (TileSetX)) {
				srcxpos -= (TileSetX);
				srcypos++;
			}

			//We create the entity
			auto& TileEntity = scene->entityManager->addEntity();
			TileEntity.addComponent<Transform2D>(TileSize * x, TileSize * y);
			TileEntity.addComponent<FixedSpriteComponent>(TextureFilepath, TileSize, TileSize, (srcxpos - 1) * TileSize, (srcypos)*TileSize, TileSize);
			//The entity is added to a group. Group zero is usually for the map.
			TileEntity.AddGroup(zerolayer);

			mapTxt.ignore();
		}
	}
	mapTxt.close();
	MapW = tilesX * TileSize;
	MapH = tilesY * TileSize;
}

void Map::LoadDetailMap(const char* TextureFilepath, const char* TxtFilepath, int TileSize, int tilesX, int tilesY, int nullTile = 0) {
	int tile;
	std::fstream mapTxt;

	SDL_Texture* text = scene->resourceManager->TakeTexture(TextureFilepath);
	int TextureW, TextureH;

	SDL_QueryTexture(text, NULL, NULL, &TextureW, &TextureH);
	int TileSetX = (TextureW / TileSize);
	int TileSetY = (TextureH / TileSize);

	mapTxt.open(TxtFilepath);
	for (int y = 0; y < tilesY; y++) {
		for (int x = 0; x < tilesX; x++) {
			mapTxt >> tile;
			if (tile != nullTile) {
				int srcxpos = tile;
				int srcypos = 0;
				while (srcxpos > (TileSetX)) {
					srcxpos -= (TileSetX);
					srcypos++;
				}

				auto& TileEntity = scene->entityManager->addEntity();
				TileEntity.addComponent<Transform2D>(TileSize * x, TileSize * y); \
				TileEntity.addComponent<FixedSpriteComponent>(TextureFilepath, TileSize, TileSize, (srcxpos - 1) * TileSize, (srcypos)*TileSize, TileSize);
				TileEntity.AddGroup(firstlayer);
			}

			mapTxt.ignore();
		}
	}

	mapTxt.close();

	MapW = tilesX * TileSize;
	MapH = tilesY * TileSize;
}

void Map::LoadCollisionMap(const char* TextureFilepath, const char* TxtFilepath, int TileSize, int tilesX, int tilesY, int nullTile = 0) {
	int tile;
	std::fstream mapTxt;

	SDL_Texture* text = scene->resourceManager->TakeTexture(TextureFilepath);

	int TextureW, TextureH;
	SDL_QueryTexture(text, NULL, NULL, &TextureW, &TextureH);
	int TileSetX = (TextureW / TileSize);
	int TileSetY = (TextureH / TileSize);

	mapTxt.open(TxtFilepath);

	for (int y = 0; y < tilesY; y++) {
		for (int x = 0; x < tilesX; x++) {
			mapTxt >> tile;
			//if the tile is not equal to the null tile, we render it.
			if (tile != nullTile) {
				int srcxpos = tile;
				int srcypos = 0;
				while (srcxpos > (TileSetX)) {
					srcxpos -= (TileSetX);
					srcypos++;
				}

				auto& TileEntity = scene->entityManager->addEntity();
				TileEntity.addComponent<Transform2D>(TileSize * x, TileSize * y); \
				//we will render the collision tiles as a transparent sprite that overlaps the map.
				TileEntity.addComponent<FixedSpriteComponent>(nullptr, TileSize, TileSize, 0, 0, TileSize);
				TileEntity.addComponent<BoxCollider>("tile");
				TileEntity.getComponent<BoxCollider>().showHitbox = true;
				TileEntity.AddGroup(secondlayer);
			}
			
			mapTxt.ignore();
		}
	}

	mapTxt.close();

	MapW = tilesX * TileSize;
	MapH = tilesY * TileSize;
}

void Map::SetScene(Scene* scene_) {
	scene = scene_;
}
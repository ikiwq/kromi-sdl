#include "Map.h"
#include "Scene.h"
#include "Transform2D.h"
#include "FixedSpriteComponent.h"

Map::Map() {

}

Map::~Map() {
	Tiles.clear();
	scene = nullptr;
}

void Map::LoadMap(const char* TextureFilepath, const char* TxtFilepath, int TileSize, int tilesX, int tilesY) {
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

			int srcxpos = tile;
			int srcypos = 0;
			while (srcxpos > (TileSetX)) {
				srcxpos -= (TileSetX);
				srcypos++;
			}

			auto& TileEntity = scene->entityManager->addEntity();
			TileEntity.addComponent<Transform2D>(TileSize * x, TileSize * y);
			TileEntity.addComponent<FixedSpriteComponent>(TextureFilepath, TileSize, TileSize, (srcxpos - 1) * TileSize, (srcypos)*TileSize, TileSize);
			TileEntity.AddGroup(zerolayer);

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
#include "FixedSpriteComponent.h"
#include "ResourceManager.h"
#include "Graphics.h"

FixedSpriteComponent::FixedSpriteComponent(int width_, int height_, int r_, int g_, int b_)
		: HasAnimation(false), affectedByCamera(true) {
	resourceManager = ResourceManager::GetIstance();
	graphicsManager = GraphicsManager::GetIstance();

	width = width_;
	height = height_;

	destRect.w = width;
	destRect.h = height;
	destRect.x = 0;
	destRect.y = 0;

	red = r_;
	green = g_;
	blue = b_;
	alpha = 255;
}

FixedSpriteComponent::FixedSpriteComponent(const char* filepath, int width_, int height_) 
		:HasAnimation(false), affectedByCamera(true), isSprite(true) {
	resourceManager = ResourceManager::GetIstance();
	graphicsManager = GraphicsManager::GetIstance();

	SpriteTexture = resourceManager->TakeTexture(filepath);
	SDL_QueryTexture(SpriteTexture, NULL, NULL, &textureW, &textureH);

	width = width_;
	height = height_;

	destRect.w = width;
	destRect.h = height;
	destRect.x = 0;
	destRect.y = 0;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = textureW;
	srcRect.h = textureH;

}

FixedSpriteComponent::FixedSpriteComponent(const char* filepath, int width_, int height_, int srcx, int srcy, int srcwh) 
		:HasAnimation(false), affectedByCamera(true), isSprite(true) {
	resourceManager = ResourceManager::GetIstance();
	graphicsManager = GraphicsManager::GetIstance();

	SpriteTexture = resourceManager->TakeTexture(filepath);
	SDL_QueryTexture(SpriteTexture, NULL, NULL, &textureW, &textureH);

	width = width_;
	height = height_;

	destRect.w = width;
	destRect.h = height;
	destRect.x = 0;
	destRect.y = 0;

	srcRect.x = srcx;
	srcRect.y = srcy;
	srcRect.w = srcRect.h = srcwh;

}

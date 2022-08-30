#pragma once

#include "ECS.h"
#include "SDL.h"
#include "Transform2D.h"

class GraphicsManager;

class FixedSpriteComponent : public Component {
public:
	bool HasAnimation;
	bool affectedByCamera;
	bool isSprite;
	int width, height;
	int red, green, blue, alpha;
	SDL_Rect srcRect, destRect, startdestRect;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
private:
	ResourceManager* resourceManager;
	GraphicsManager* graphicsManager;

	Transform2D* Transform;
	SDL_Texture* SpriteTexture;

	int textureW, textureH;

public:
	FixedSpriteComponent(int width_, int height_, int r_, int g_, int b_);

	FixedSpriteComponent(const char* filepath, int width_, int height_);

	FixedSpriteComponent(const char* filepath, int width_, int height_, int srcx, int srcy, int srcwh);

	~FixedSpriteComponent() {
		graphicsManager = nullptr;
		resourceManager = nullptr;
		Transform = nullptr;
	}

	bool Init() override {
		if (! owner->hasComponent <Transform2D>()) {
			std::cout << "Entity must have a Transform2D component!" << std::endl;
			return false;
		}
		if (owner->hasComponent<FixedSpriteComponent>()) {
			std::cout << "Entity has already got Fixed Sprite Component!";
			return false;
		}
		Transform = &owner->getComponent<Transform2D>();

		destRect.x = Transform->GetPosition().x;
		destRect.y = Transform->GetPosition().y;
		return true;
	}

	void Update() override {
		if (affectedByCamera) {
			destRect.x = (Transform->GetPosition().x - owner->EntityScene->Camera.x) * Transform->GetScale().x;;
			destRect.y = (Transform->GetPosition().y - owner->EntityScene->Camera.y) * Transform->GetScale().y;;
			destRect.w = width * Transform->GetScale().x;
			destRect.h = height * Transform->GetScale().y;
		}
		else {
			destRect.x = Transform->GetPosition().x;
			destRect.y = Transform->GetPosition().y ;
		}
	}

	void Render() override {
		if (isSprite) {
			SDL_RenderCopyEx(graphicsManager->GetRenderer(), SpriteTexture, &srcRect, &destRect, Transform->GetRotation(), NULL, flip);
		}
		else {
			SDL_SetRenderDrawColor(graphicsManager->GetRenderer(), red, green, blue, alpha);
			SDL_RenderDrawRect(graphicsManager->GetRenderer(), &destRect);
			SDL_RenderFillRect(graphicsManager->GetRenderer(), &destRect);
		}
	}

	SDL_Rect GetDestRect() {
		return destRect;
	}
};
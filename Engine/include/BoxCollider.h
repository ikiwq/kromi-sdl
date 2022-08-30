#pragma once

#include <string>
#include <iostream>
#include "SDL.h"
#include "ECS.h"

class Transform2D;
class GameManager;
class FixedSpriteComponent;
class GraphicsManager;

class BoxCollider : public Component {
public:
	SDL_Rect BoxColliderRect;
	std::string tag;
	bool showHitbox;
private:
	FixedSpriteComponent* Sprite;
	Transform2D* Transform;
	GraphicsManager* graphicsManager;

public:
	BoxCollider(std::string tag_);

	bool Init() override;

	void Update() override;

	void Render() override;

};
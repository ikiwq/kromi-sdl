#pragma once
#include "ECS.h"

class Transform2D;
class FixedSpriteComponent;
class ResourceMamager;
class GraphicsManager;

class TextComponent : public Component {
public:
	SDL_Rect TextRect;
	int size;
	int OffsetX, OffsetY;
	bool isCentered;

private:
	std::string Text;
	std::string FontPath;
	SDL_Texture* textTexture;
	SDL_Color textColor;

public:
	Transform2D* Transform;
	FixedSpriteComponent* Sprite;
	ResourceManager* resourceManager;
	GraphicsManager* graphicsManager;

	TextComponent(std::string text, std::string filepath, int size_, SDL_Color& color, bool centered);

	~TextComponent();

	bool Init() override;
	void Render() override;
	void Update() override;

	void SetText();
};
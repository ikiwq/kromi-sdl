#include "TextComponent.h"
#include "ResourceManager.h"
#include "Transform2D.h"
#include "FixedSpriteComponent.h"

TextComponent::TextComponent(std::string text, std::string filepath, int size_, SDL_Color& color, bool centered) {
	Text = text;
	FontPath = filepath;
	textColor = color;

	size = size_;

	isCentered = centered;
}

TextComponent::~TextComponent() {
	Transform = nullptr;
	resourceManager = nullptr;
	graphicsManager = nullptr;
	SDL_DestroyTexture(textTexture);
}

bool TextComponent::Init() {
	if (!owner->hasComponent<Transform2D>()) {
		std::cout << "Entity must have Transform2D component!" << std::endl;
		return false;
	}
	if (!owner->hasComponent<FixedSpriteComponent>()) {
		std::cout << "Entity must have fixed sprite component!" << std::endl;
		return false;
	}
	if (owner->hasComponent<TextComponent>()) {
		std::cout << "Entity has already Text Component!" << std::endl;
		return false;
	}
	Transform = &owner->getComponent<Transform2D>();
	Sprite = &owner->getComponent<FixedSpriteComponent>();
	std::cout << Transform << std::endl;


	resourceManager = ResourceManager::GetIstance();
	graphicsManager = GraphicsManager::GetIstance();

	SetText();

	if (isCentered) {
		OffsetX = (Sprite->destRect.w - Pos.w) / 2;
		OffsetY = (Sprite->destRect.h - Pos.h) / 2;
	}

	Pos.x = Transform->GetPosition().x + OffsetX;
	Pos.y = Transform->GetPosition().y + OffsetY;

	return true;
}

void TextComponent::SetText() {
	SDL_Surface* surface = TTF_RenderText_Blended(resourceManager->TakeFont(FontPath, size), Text.c_str(), textColor);
	textTexture = SDL_CreateTextureFromSurface(graphicsManager->GetRenderer(), surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(textTexture, nullptr, nullptr, &Pos.w, &Pos.h);
}

void TextComponent::Render() {
	SDL_RenderCopy(graphicsManager->GetRenderer(), textTexture, nullptr, &Pos);
}
void TextComponent::Update() {
	if (isCentered) {
		OffsetX = (Sprite->destRect.w - Pos.w) / 2;
		OffsetY = (Sprite->destRect.h - Pos.h) / 2;
	}
	Pos.x = Transform->GetPosition().x + OffsetX;
	Pos.y = Transform->GetPosition().y + OffsetY;
}
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Transform2D.h"
#include "FixedSpriteComponent.h"

//The text component renders a text. It can be centered inside a sprite.
TextComponent::TextComponent(std::string text, std::string filepath, int size_, 
	SDL_Color& color, bool centered): OffsetX(0), OffsetY(0) {

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
	//Dependencies
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

	resourceManager = ResourceManager::GetIstance();
	graphicsManager = GraphicsManager::GetIstance();

	SetText();

	//If the sprite is centered, its offset position from the top left will be calculated automatically
	//and will be sum with the sprite position.
	if (isCentered) {
		OffsetX = (Sprite->destRect.w - TextRect.w) / 2;
		OffsetY = (Sprite->destRect.h - TextRect.h) / 2;
	}

	TextRect.x = Transform->GetPosition().x + OffsetX;
	TextRect.y = Transform->GetPosition().y + OffsetY;

	return true;
}

void TextComponent::SetText() {
	SDL_Surface* surface = TTF_RenderText_Blended(resourceManager->TakeFont(FontPath, size), Text.c_str(), textColor);
	textTexture = SDL_CreateTextureFromSurface(graphicsManager->GetRenderer(), surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(textTexture, nullptr, nullptr, &TextRect.w, &TextRect.h);
}

void TextComponent::Render() {
	SDL_RenderCopy(graphicsManager->GetRenderer(), textTexture, nullptr, &TextRect);
}
void TextComponent::Update() {
	//Update the position and centered position
	if (isCentered) {
		OffsetX = (Sprite->destRect.w - TextRect.w) / 2;
		OffsetY = (Sprite->destRect.h - TextRect.h) / 2;
	}
	TextRect.x = Transform->GetPosition().x + OffsetX;
	TextRect.y = Transform->GetPosition().y + OffsetY;
}
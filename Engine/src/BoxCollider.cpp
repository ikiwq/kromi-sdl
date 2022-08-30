#include "BoxCollider.h"
#include "Transform2D.h"
#include "FixedSpriteComponent.h"
#include "Graphics.h"

BoxCollider::BoxCollider(std::string tag_) : showHitbox(false) {
	tag = tag_;
	graphicsManager = GraphicsManager::GetIstance();
}

bool BoxCollider::Init() {
	if (!owner->hasComponent<FixedSpriteComponent>()) {
		std::cout << "Entity must have a fixed sprite component!" << std::endl;
		return false;
	}
	if (!owner->hasComponent<Transform2D>()) {
		std::cout << "Entity must have a transform 2D component!" << std::endl;
		return false;
	}
	if (owner->hasComponent<BoxCollider>()) {
		std::cout << "Entity has already got a box collider component!" << std::endl;
		return false;
	}

	Sprite = &owner->getComponent<FixedSpriteComponent>();
	Transform = &owner->getComponent<Transform2D>();

	BoxColliderRect.x = Sprite->GetDestRect().x;
	BoxColliderRect.y = Sprite->GetDestRect().y;
	BoxColliderRect.w = Sprite->GetDestRect().w;
	BoxColliderRect.h = Sprite->GetDestRect().h;

	return true;
}

void BoxCollider::Update() {
	BoxColliderRect.x = Sprite->GetDestRect().x;
	BoxColliderRect.y = Sprite->GetDestRect().y;
	BoxColliderRect.w = Sprite->GetDestRect().w;
	BoxColliderRect.h = Sprite->GetDestRect().h;

	if (Transform->GetPosition().x <= 0) {
		Transform->SetPosition(0, Transform->GetPosition().y);
	}
	if (Transform->GetPosition().x + BoxColliderRect.w >= owner->EntityScene->SceneSizeX) {
		Transform->SetPosition(owner->EntityScene->SceneSizeX - BoxColliderRect.w, Transform->GetPosition().y);
	}

	if (Transform->GetPosition().y <= 0) {
		Transform->SetPosition(Transform->GetPosition().x , 0);
	}
	if (Transform->GetPosition().y + BoxColliderRect.h >= owner->EntityScene->SceneSizeY) {
		Transform->SetPosition(Transform->GetPosition().x, owner->EntityScene->SceneSizeY-BoxColliderRect.y);
	}
}

void BoxCollider::Render() {
	if (showHitbox) {
		SDL_SetRenderDrawColor(graphicsManager->GetRenderer(), 255, 255, 255, 255);
		SDL_RenderDrawRect(graphicsManager->GetRenderer(), &BoxColliderRect);
	}
}
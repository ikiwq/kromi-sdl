#include "BoxCollider.h"
#include "Transform2D.h"
#include "FixedSpriteComponent.h"
#include "Graphics.h"

BoxCollider::BoxCollider(std::string tag_) : showHitbox(false) {
	//Every box collider has a tag
	tag = tag_;
	graphicsManager = GraphicsManager::GetIstance();
}

bool BoxCollider::Init() {
	//Dependencies
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
	//Get the Fixed Sprite and Transform component from its owner Entity
	Sprite = &owner->getComponent<FixedSpriteComponent>();
	Transform = &owner->getComponent<Transform2D>();

	//Hitbox rect will be the same as the destination rect of the sprite

	LastSafePosition.x = BoxColliderRect.x = Sprite->GetDestRect().x;
	LastSafePosition.y = BoxColliderRect.y = Sprite->GetDestRect().y;
	BoxColliderRect.w = Sprite->GetDestRect().w;
	BoxColliderRect.h = Sprite->GetDestRect().h;

	return true;
}

void BoxCollider::Update() {
	//Updating the Hitbox rectangle by taking the destination rect of the sprite
	//If the Collider is colliding, go to the last safe position
	
	if (!isColliding) {
		LastSafePosition.x = (int)Transform->GetPosition().x;
		LastSafePosition.y = (int)Transform->GetPosition().y;

		BoxColliderRect.x = Sprite->GetDestRect().x;
		BoxColliderRect.y = Sprite->GetDestRect().y;
	}
	else {
		if (Transform->GetVelocity().x > 0) {
			Transform->Position.x = LastSafePosition.x - 10;
		}
		else if(Transform->GetVelocity().x < 0) {
			Transform->Position.x = LastSafePosition.x + 10;
		}
		
		if (Transform->GetVelocity().y > 0) {
			Transform->Position.y = LastSafePosition.y - 10;
		}
		else if (Transform->GetVelocity().y < 0) {
			Transform->Position.y = LastSafePosition.y + 10;
		}
		isColliding = false;
	}
	
	BoxColliderRect.w = Sprite->GetDestRect().w;
	BoxColliderRect.h = Sprite->GetDestRect().h;

	//Prevent the Entity from going out the Scene
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
	//if this is set to true, then the hit box will be renderered aroumd the player
	if (showHitbox) {
		SDL_SetRenderDrawColor(graphicsManager->GetRenderer(), 255, 255, 255, 255);
		SDL_RenderDrawRect(graphicsManager->GetRenderer(), &BoxColliderRect);
	}
}
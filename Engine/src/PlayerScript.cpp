#include "PlayerScript.h"
#include "Transform2D.h"
#include "FixedSpriteComponent.h"
#include "AnimationComponent.h"
#include "InputComponent.h"
#include "Timer.h"

PlayerScript::PlayerScript() {
	facingRight = true;
	isAnimating = false;
	isStanding = true;
	isAttacking = false;
	isRunning = false;
}

PlayerScript::~PlayerScript() {
	Transform = nullptr;
	Sprite = nullptr;
	Animation = nullptr;
	Input = nullptr;
	Timer = nullptr;
}

bool PlayerScript::Init() {
	if (!owner->hasComponent<Transform2D>()) {
		std::cout << "Entity must have a Transform2D component!" << std::endl;
		return false;
	}
	if (!owner->hasComponent<FixedSpriteComponent>()) {
		std::cout << "Entity must have a fixed sprite component!" << std::endl;
		return false;
	}
	if (!owner->hasComponent<AnimationComponent>()) {
		std::cout << "Entity must have an Animation component!" << std::endl;
		return false;
	}
	if (!owner->hasComponent<InputComponent>()) {
		std::cout << "Entity must have an Input component!" << std::endl;
		return false;
	}

	Transform = &owner->getComponent<Transform2D>();
	Sprite = &owner->getComponent<FixedSpriteComponent>();
	Animation = &owner->getComponent<AnimationComponent>();
	Input = &owner->getComponent<InputComponent>();
	Timer = Timer::GetInstance();

	return true;
}

void PlayerScript::Update() {
	Input->UpdateCurrInput();

	if (Transform->Velocity.x > 0) {
		facingRight = true;
		Sprite->flip = SDL_FLIP_NONE;
	}
	if (Transform->Velocity.x < 0) {
		facingRight = true;
		Sprite->flip = SDL_FLIP_HORIZONTAL;
	}

	if (Transform->Velocity.x != 0 || Transform->Velocity.y != 0) {
		Sprite->srcRect.y = 32;
		Animation->frameCount = 9;
	}
	else {
		Animation->frameCount = 10;
		Sprite->srcRect.y = 0;
	}

	if (Input->KeyPress(SDL_SCANCODE_W)) {
		Transform->SetVelocity(Transform->Velocity.x, Transform->Velocity.y -= 200);
	}
	if (Input->KeyRelease(SDL_SCANCODE_W)) {
		Transform->SetVelocity(Transform->Velocity.x, Transform->Velocity.y += 200);
	}

	if (Input->KeyPress(SDL_SCANCODE_S)) {
		Transform->SetVelocity(Transform->Velocity.x, Transform->Velocity.y += 200);
	}
	if (Input->KeyRelease(SDL_SCANCODE_S)) {
		Transform->SetVelocity(Transform->Velocity.x, Transform->Velocity.y -= 200);
	}

	if (Input->KeyPress(SDL_SCANCODE_A)) {
		Transform->SetVelocity(Transform->Velocity.x -= 200, Transform->Velocity.y);
	}
	if (Input->KeyRelease(SDL_SCANCODE_A)) {
		Transform->SetVelocity(Transform->Velocity.x += 200, Transform->Velocity.y);
	}

	if (Input->KeyPress(SDL_SCANCODE_D)) {
		Transform->SetVelocity(Transform->Velocity.x += 200, Transform->Velocity.y);
	}
	if (Input->KeyRelease(SDL_SCANCODE_D)) {
		Transform->SetVelocity(Transform->Velocity.x -= 200, Transform->Velocity.y);
	}

	Input->UpdatePrevInput();
}
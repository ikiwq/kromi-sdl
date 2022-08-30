#include "AnimationComponent.h"

#include "Timer.h"
#include "FixedSpriteComponent.h"

AnimationComponent::AnimationComponent(int fW, int fH, int fC, float aDuration) :
	spacingX(0), spacingY(0), offsetX(0), offsetY(0), AccumdT(0), canAnimate(true) {
	timer = Timer::GetInstance();
	frameW = fW;
	frameH = fH;

	frameCount = fC;
	animationDuration = aDuration;
}

AnimationComponent::~AnimationComponent() {
	timer = nullptr;
	Sprite = nullptr;
}

bool AnimationComponent::Init() {
	if (!owner->hasComponent<FixedSpriteComponent>()) {
		std::cout << "Entity must have Fixed Sprite Component!" << std::endl;
		return false;
	}
	if (owner->hasComponent<AnimationComponent>()) {
		std::cout << "Entity has already got Animation Component!";
		return false;
	}
	Sprite = &owner->getComponent<FixedSpriteComponent>();
	Sprite->HasAnimation = true;

	Sprite->srcRect.x = offsetX;
	Sprite->srcRect.y = offsetY;
	Sprite->srcRect.w = frameW;
	Sprite->srcRect.h = frameH;
	return true;
}

void AnimationComponent::Update() {
	if (canAnimate) {
		AccumdT += timer->GetPhysicsDt();
		if (AccumdT > animationDuration) {
			if (Sprite->srcRect.x < (spacingX + frameW) * (frameCount - 2)) {
				Sprite->srcRect.x += spacingX + frameW;
			}
			else {
				Sprite->srcRect.x = 0;
			}
			AccumdT = 0;
		}
	}
}